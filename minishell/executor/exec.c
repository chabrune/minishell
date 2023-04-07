/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:40:37 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/07 16:55:18 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// int	executor(t_simple_cmds **head, t_tools *tools)
// {
// 	int i;
// 	t_simple_cmds *curr;
// 	int pipes[2];
// 	int fd_in;

// 	fd_in = STDIN_FILENO;
// 	curr = *head;
// 	while(curr)
// 	{
// 		if(curr->next)
// 			pipe(pipes);
// 		curr = curr->next;
// 	}
	// i = count_cmd(head);
	// if(i == 1)
	// 	one_command(head, tools);
	// else
	// 	multiple_commands(head, tools);
// }

int	one_command(t_simple_cmds **head, t_tools *tools)
{
	t_simple_cmds *curr;
	int pid;
	curr = *head;
	
	//if cmd == cd / exit / export / unset --> Exec without child
	// // BAH NON si cmd == cd / exit / export / unset  --> tu appelles le builtins que Emma a coder
	// if(curr->redirections->str || curr->redirections->token == GREAT || curr->redirections->token == LESS)
	// 	redir_is_fun(head);
	tools->path = find_path(tools->envp);
	tools->paths = ft_split(tools->path, ':');
	tools->cmd = get_cmd(tools->paths, curr->str[0]);
	pid = fork();
	if(pid == -1)
	{
		perror("Fork : ");
		return(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		execve(tools->cmd, curr->str, tools->envp);
		perror("Exceve : ");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	return(0);
}

int **alloc_pipes(t_simple_cmds **head)
{
    int i;
    int j;
    int **pipes;

    j = count_cmd(head);
    i = -1;
	printf("%d\n", j);
    pipes = ft_calloc(sizeof(int *), j + 1);
    if (!pipes)
        return (NULL);
    while (++i < j)
    {
        pipes[i] = ft_calloc(sizeof(int), 3);
        if (!pipes[i])
            return (NULL);
    }
    return (pipes);
}

int *alloc_pids(t_simple_cmds **head)
{
	int *pids;
	int j;

	j = count_cmd(head);
	pids = ft_calloc(sizeof(int), j + 1);
	if(!pids)
		return(NULL);
	return(pids);
}

void	free_pipes_and_pids(t_simple_cmds **head, int **pipes, int *pids)
{
	int i;
	int j;

	j = count_cmd(head);
	i = -1;
	while(++i < j - 1)
	{
    	free(pipes[i]);
	}
	free(pipes);
	free(pids);
}

int	multiple_commands(t_simple_cmds **head, t_tools	*tools)
{
	t_simple_cmds *tmp;
	int i;
	int j;
	int **pipes;
	int *pids;

	pipes = alloc_pipes(head);
	pids = alloc_pids(head);
	j = count_cmd(head);
	i = -1;
	tmp = *head;
	while(++i < j)
	{
		if(i < j - 1)
		{
			if(pipe(pipes[i]) == -1)
			{
				perror("pipe");
				return(EXIT_FAILURE);
			}
		}
		pids[i] = fork();
		if(pids[i] == -1)
		{
			perror("fork");
			return(EXIT_FAILURE);
		}
		else if(pids[i] == 0)
		{
			child_process(tmp, tools, head, pipes, &i);
		}
		else
			parent_process(pipes, pids);
		tmp = tmp->next;
	}
	free_pipes_and_pids(head, pipes, pids);
	return(0);
}

int	child_process(t_simple_cmds *curr, t_tools *tools, t_simple_cmds **head, int **pipes, int *i)
{
	int j;

	j = count_cmd(head);
	if(curr->prev && dup2(pipes[*i][0], STDIN_FILENO) == -1)
	{
		perror("dup2-1");
		return(EXIT_FAILURE);
	}
	close(pipes[*i][0]);
	if(curr->next && dup2(pipes[*i][1], STDOUT_FILENO) == -1)
	{
		perror("dup2-2");
		return(EXIT_FAILURE);
	}
	close(pipes[*i][1]);
	tools->path = find_path(tools->envp);
	tools->paths = ft_split(tools->path, ':');
	tools->cmd = get_cmd(tools->paths, curr->str[0]);
	execve(tools->cmd, curr->str, tools->envp);
	free(tools->path);
	free(tools->paths);
	free(tools->cmd);
	perror("Execve :");
	exit(EXIT_FAILURE);
	return(0);
}

void	parent_process(int **pipes, int *pids)
{
	int j;
	int k;
	int i;

	i = -1;
	j = -1;
	while(pipes[++j])
	{
		k = -1;
		while(pipes[j][++k])
			close(pipes[j][k]);
	}
	while(pids[++i])
		waitpid(pids[i], NULL, 0);
}

char	*find_path(char **env)
{
	while (strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

//appel si redir
int	redir_is_fun(t_simple_cmds **head)
{
	t_simple_cmds *tmp;
	tmp = *head;
	int fdout;

	while(tmp)
	{
		while(tmp->redirections)
		{
			if(tmp->redirections->token == LESS)
			{
				fdout = open(tmp->redirections->prev->str, O_RDONLY);
				if(fdout == -1)
				{
					perror("Open : ");
					return(EXIT_FAILURE);
				}
				if(dup2(fdout, STDIN_FILENO) == -1)
				{
					perror("Dup2 :");
					return(EXIT_FAILURE);
				}
			}
			tmp->redirections = tmp->redirections->next;
		}
		tmp = tmp->next;
	}
	return(0);
}

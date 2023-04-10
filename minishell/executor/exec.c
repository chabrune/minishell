/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:40:37 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/10 17:39:05 by chabrune         ###   ########.fr       */
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

// int	one_command(t_simple_cmds **head, t_tools *tools)
// {
// 	t_simple_cmds *curr;
// 	int pid;
// 	curr = *head;
	
// 	//if cmd == cd / exit / export / unset --> Exec without child
// 	// // BAH NON si cmd == cd / exit / export / unset  --> tu appelles le builtins que Emma a coder
// 	// if(curr->redirections->str || curr->redirections->token == GREAT || curr->redirections->token == LESS)
// 	// 	redir_is_fun(head);
// 	tools->path = find_path(tools->envp); //check unset path
// 	tools->paths = ft_split(tools->path, ':');
// 	tools->cmd = get_cmd(tools->paths, curr->str[0]);
// 	pid = fork();
// 	if(pid == -1)
// 	{
// 		perror("Fork : ");
// 		return(EXIT_FAILURE);
// 	}
// 	else if(pid == 0)
// 	{
// 		execve(tools->cmd, curr->str, tools->envp);
// 		perror("Exceve : ");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 		waitpid(pid, NULL, 0);
// 	return(0);
// }

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

int	ft_fork(t_tools *tools, t_simple_cmds *curr, int fd_in, int pipes[2])
{
	static int i = 0;

	tools->pid[i] = fork();
	if(tools->pid[i] == -1)
	{
		perror("fork");
		return(EXIT_FAILURE);
	}
	if(tools->pid[i] == 0)
		dup_cmd(curr, fd_in, pipes, tools);
	i++;
	return(EXIT_SUCCESS);
}

int	ft_check_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	int fd_in;
	(void)tools;
	if(0)
	{
		printf("COUCOU\n");
		close(tools->pipes[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = tools->pipes[0];
	return(fd_in);
}

int	multiple_commands(t_simple_cmds **head, t_tools	*tools)
{
	t_simple_cmds *tmp;
	int fd_in;
	int j;
	int pipes[2];

	j = count_cmd(head);
	tools->pid = ft_calloc(sizeof(int), j + 1);
	fd_in = STDIN_FILENO;
	tmp = *head;
	while(tmp)
	{
		if(tmp->next)
		{
			if(pipe(pipes) == -1)
			{
				perror("pipe");
				return(EXIT_FAILURE);
			}
		}
		ft_fork(tools, tmp, fd_in, pipes);
		close(pipes[1]);
		if(tmp->prev)
			close(fd_in);
		fd_in = ft_check_heredoc(tools, tmp);
		if(tmp->next)
			tmp = tmp->next;
		else
			break;
	}
	wait_process(tools);
	return(0);
}

int	handle_cmd(t_simple_cmds *curr, t_tools *tools)
{
	int exit_code;

	exit_code = 0;
	if(curr->str[0][0] != '\0')
	{
		tools->cmd = get_cmd(tools->paths, curr->str[0]);
		if(tools->cmd)
		{
			execve(tools->cmd, curr->str, tools->envp);
			free(tools->path);
			free(tools->paths);
			free(tools->cmd);
			perror("Execve :");
			exit(EXIT_FAILURE);
		}
	}
	exit(exit_code);
}

int	dup_cmd(t_simple_cmds *curr, int fd_in, int pipes[2], t_tools *tools)
{
	if(curr->prev && dup2(pipes[0], STDIN_FILENO) == -1)
	{
		perror("dup2-1");
		return(EXIT_FAILURE);
	}
	close(pipes[0]);
	if(curr->next && dup2(pipes[1], STDOUT_FILENO) == -1)
	{
		perror("dup2-2");
		return(EXIT_FAILURE);
	}
	close(pipes[1]);
	if(curr->prev)
		close(fd_in);
	handle_cmd(curr, tools);
	return(0);
}

// int	child_process(t_simple_cmds *curr, t_tools *tools, int fd_in)
// {
// 	if(curr->prev && dup2(fd_in, STDIN_FILENO) == -1)
// 	{
// 		perror("dup2-1");
// 		return(EXIT_FAILURE);
// 	}
// 	close(tools->pipes[0]);
// 	if(curr->next && dup2(tools->pipes[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2-2");
// 		return(EXIT_FAILURE);
// 	}
// 	close(tools->pipes[1]);
// 	if(curr->prev)
// 		close(fd_in);
// 	tools->path = find_path(tools->envp);
// 	tools->paths = ft_split(tools->path, ':');
// 	tools->cmd = get_cmd(tools->paths, curr->str[0]);
// 	execve(tools->cmd, curr->str, tools->envp);
// 	free(tools->path);
// 	free(tools->paths);
// 	free(tools->cmd);
// 	perror("Execve :");
// 	exit(EXIT_FAILURE);
// 	return(0);
// }

void	wait_process(t_tools *tools)
{
	int i;

	i = -1;
	while(tools->pid[++i])
		waitpid(tools->pid[i], NULL, 0);
	waitpid(tools->pid[i], NULL, 0);
}

char	*find_path(char **env)
{
	while (strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

// char	*get_cmd(t_simple_cmds *curr, t_tools *tools)
// {
// 	char *tmp;
// 	char *command;
// 	int i;

// 	i = -1;
// 	tools->paths = ft_split(tools->path, ':');
// 	tools->path = find_path(tools->envp);
// 	while (tools->paths[++i])
// 	{
// 		tmp = ft_strjoin(tools->paths[i], "/");
// 		command = ft_strjoin(tmp, curr->str[0]);
// 		free(tmp);
// 		if (access(command, F_OK) == 0)
// 		{
// 			execve(command, curr->str, tools->envp);
// 			free(tools->path);
// 			free(tools->paths);
// 			free(tools->cmd);
// 			free(command);
// 			perror("Execve :");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (NULL);
// }

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

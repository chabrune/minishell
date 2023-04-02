/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:40:37 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/02 19:11:25 by chabrune         ###   ########.fr       */
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

int	multiple_commands(t_simple_cmds **head, t_tools	*tools)
{
	t_simple_cmds *tmp;
	int i;
	int fd_in;
	int fd[2];

	i = 0;
	tmp = *head;
	fd_in = STDIN_FILENO;
	tools->pid = ft_calloc(sizeof(int), count_cmd(head));
	while(tmp)
	{
		if(tmp->next)
		{
			if(pipe(fd) == -1)
			{
				perror("Fork :");
				return(EXIT_FAILURE);
			}
		}
		close(fd[1]);
		if(tools->pid[i] == -1)
		{
			perror("Fork :");
			return(EXIT_FAILURE);
		}
		else if(tools->pid[i] == 0)
			child_process(tmp, tools, fd_in, fd);
		else
			parent_process(tools, &i);
		i++;
		if(tmp->next)
			tmp = tmp->next;
		else
			break;
	}
	return(0);
}


int	child_process(t_simple_cmds *curr, t_tools *tools, int fd_in, int fd[2])
{
	if (curr->prev && dup2(fd_in, STDIN_FILENO) < 0)
	{
		perror("Dup2-1 : ");
		return(EXIT_FAILURE);
	}
	close(fd[0]);
	if (curr->next && dup2(fd[1], STDOUT_FILENO) < 0)
	{
		perror("Dup2-2 : ");
		return(EXIT_FAILURE);
	}
	close(fd[1]);
	if (curr->prev)
		close(fd_in);
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

void	parent_process(t_tools *tools, int *i)
{
	close(tools->fd[0]);
	close(tools->fd[1]);
	waitpid(tools->pid[*i], NULL, 0);
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
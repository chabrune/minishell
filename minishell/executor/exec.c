/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:40:37 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/13 16:34:41 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	one_command(t_simple_cmds **head, t_tools *tools)
{
	t_simple_cmds *curr;
	int pid;
	curr = *head;
	//if cmd == cd / exit / export / unset --> Exec without child
	// // BAH NON si cmd == cd / exit / export / unset  --> tu appelles le builtins que Emma a coder
	// if(curr->redirections->str || curr->redirections->token == GREAT || curr->redirections->token == LESS)
	// 	redir_is_fun(head);
	pid = fork();
	if(pid == -1)
	{
		perror("Fork : ");
		return(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		tools->path = find_path(tools->envp); //check unset path
		tools->paths = ft_split(tools->path, ':');
		tools->cmd = get_cmd(curr, tools);
		if(tools->cmd)
			execve(tools->cmd, curr->str, tools->envp);
		perror("Exceve : ");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	return(0);
}

int	ft_fork(t_tools *tools, t_simple_cmds *curr, int fd_in, int pipes[2], t_simple_cmds **head, int *i)
{
	int j;
	j = -1;
	tools->pid[*i] = fork();
	if(tools->pid[*i] == -1)
	{
		perror("fork");
		return(EXIT_FAILURE);
	}
	else if(tools->pid[*i] == 0)
	{
		close(pipes[0]);
		if(curr->prev)
		{
          dup2(fd_in, STDIN_FILENO); // Redirect input from previous pipe
          close(fd_in);
		}
		if(curr->next)
		{
			dup2(pipes[1], STDOUT_FILENO); // Redirect output to next pipe
          	close(pipes[1]);
		}
		handle_cmd(curr, tools);
	}
	else
	{
        // Parent process
        close(pipes[1]); // Close unused write end
        if (*i > 0)
        	close(fd_in); // Close previous pipe
        fd_in = pipes[0]; // Save read end for next command
    }
	while(++j < count_cmd(head))
		wait(NULL);
	return(EXIT_SUCCESS);
}

int	ft_check_heredoc(t_tools *tools, t_simple_cmds *cmd, int pipes[2])
{
	int fd_in;
	(void)tools;
	if(0)
	{
		close(pipes[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = pipes[0];
	return(fd_in);
}

int	multiple_commands(t_simple_cmds **head, t_tools	*tools)
{
	t_simple_cmds *tmp;
	int fd_in;
	int j;
	int pipes[2];
	int i;

	i = 0;
	ft_memset(pipes, 0, sizeof(pipes));
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
		ft_fork(tools, tmp, fd_in, pipes, head, &i);
		fd_in = ft_check_heredoc(tools, tmp, pipes);
		if(tmp->next)
			tmp = tmp->next;
		else
			break;
		i++;
	}
	return(0);
}

int	handle_cmd(t_simple_cmds *curr, t_tools *tools)
{
	int exit_code;

	exit_code = 0;
	if(curr->str[0][0] != '\0')
	{
		tools->path = find_path(tools->envp); //check unset path
		tools->paths = ft_split(tools->path, ':');
		tools->cmd = get_cmd(curr, tools);
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

char	*find_path(char **env)
{
	while (strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}


char	*get_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	char	*tmp;
	char	*command;
	int i;

	i = 0;
	tools->path = find_path(tools->envp);
	tools->paths = ft_split(tools->path, ':');
	while (tools->paths[i])
	{
		tmp = ft_strjoin(tools->paths[i], "/");
		command = ft_strjoin(tmp, cmd->str[0]);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
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

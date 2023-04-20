/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:40:37 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/20 18:51:19 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int one_command(t_simple_cmds **head, t_tools *tools)
{
	t_simple_cmds	*curr;
	int				pid;
    int             fd;

	curr = *head;
	fd = 0;
	if (is_builtins(curr) == 1 && builtins_to_fork(curr) == 0)
		choose_bultins(tools, curr, fd);
	else
	{
		pid = fork();
		if(pid == 0)
		{
			fill_cmd_heredoc(curr);
			if(curr->hd_file_name)
			{
				fd = open(curr->hd_file_name, O_RDONLY);
				if(fd < 0)
					return(EXIT_FAILURE);
				if(dup2(fd, STDIN_FILENO) < 0)
					return(EXIT_FAILURE);
			}
			if (is_builtins(curr) == 1) 		// J'ai rajouté ce if, faut verifier aue ca casse pas tout
				choose_bultins(tools, curr, fd);
			else
			{
				handle_cmd(curr, tools);
			}
			if(fd > 0)
				close(fd);
		}
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	ft_fork(t_tools *tools, t_simple_cmds *curr, int fd_in, int pipes[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (curr->prev && dup2(fd_in, STDIN_FILENO) < 0)
			return (1);
		close(pipes[0]);
		if (curr->next && dup2(pipes[1], STDOUT_FILENO) < 0)
			return (2);
		close(pipes[1]);
		if (curr->prev)
			close(fd_in);
		// if (is_builtins(curr) == 1) 		// J'ai rajouté ce if, faut verifier aue ca casse pas tout
		// 	choose_bultins(tools, curr);
		// else
		{
			handle_cmd(curr, tools);
			// exit(1);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_check_heredoc(t_tools *tools, t_simple_cmds *cmd, int pipes[2])
{
	int	fd_in;

	(void)tools;
	if (cmd->hd_file_name)
	{
		close(pipes[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = pipes[0];
	return (fd_in);
}

int	wait_process(t_tools *tools, t_simple_cmds **head)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count_cmd(head))
	{
		if (kill(tools->pid[i], 0) == 0)
			waitpid(tools->pid[i], &status, 0);
		waitpid(tools->pid[i], &status, 0);
	}
	return (EXIT_SUCCESS);
}

int	multiple_commands(t_simple_cmds **head, t_tools *tools)
{
	t_simple_cmds	*tmp;
	int				fd_in;
	int				j;
	int				pipes[2];

	ft_memset(pipes, 0, sizeof(pipes));
	j = count_cmd(head);
	tools->pid = ft_calloc(sizeof(int), j + 1);
	fd_in = STDIN_FILENO;
	tmp = *head;
	while (tmp)
	{
		// fill_cmd_heredoc(tmp);
		if (tmp->next)
		{
			if (pipe(pipes) == -1)
			{
				perror("pipe");
				return (EXIT_FAILURE);
			}
		}
		ft_fork(tools, tmp, fd_in, pipes);
		close(pipes[1]);
		if (tmp->prev)
			close(fd_in);
		fd_in = ft_check_heredoc(tools, tmp, pipes);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	wait_process(tools, head);
	free(tools->pid);
	return (0);
}

int	handle_cmd(t_simple_cmds *curr, t_tools *tools)
{
	check_redir(curr);
	tools->path = find_path(tools->envp); //check unset path
	tools->paths = ft_split(tools->path, ':');
	tools->cmd = get_cmd(curr, tools);
	if(tools->cmd == NULL)
		perror("Execve ");
	if (tools->cmd)
	{
		execve(tools->cmd, curr->str, tools->envp);
		free(tools->path);
		free(tools->paths);
		free(tools->cmd);
		perror("Execve ");
		exit(1);
	}
	return (0);
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
	int		i;

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
	t_simple_cmds	*tmp;
	int				fdout;

	tmp = *head;
	while (tmp)
	{
		while (tmp->redirections)
		{
			if (tmp->redirections->token == LESS)
			{
				fdout = open(tmp->redirections->prev->str, O_RDONLY);
				if (fdout == -1)
				{
					perror("Open : ");
					return (EXIT_FAILURE);
				}
				if (dup2(fdout, STDIN_FILENO) == -1)
				{
					perror("Dup2 :");
					return (EXIT_FAILURE);
				}
			}
			tmp->redirections = tmp->redirections->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:51:44 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/07 15:34:55 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	dup_heredoc(t_simple_cmds *curr)
{
	int	fd;

	if (curr->hd_file_name)
	{
		fd = open(curr->hd_file_name, O_RDONLY);
		if (fd < 0)
		{
			perror("open ");
			return (EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2 ");
			return (EXIT_FAILURE);
		}
		if (fd >= 0)
			close(fd);
	}
	return (EXIT_SUCCESS);
}

int	one_command(t_simple_cmds *head, t_tools *tools, t_lexer *lexer)
{
	t_simple_cmds	*curr;
	int				pid;

	curr = head;
	if (is_builtins(curr) == 1 && builtins_to_fork(curr) == 0)
	{
		choose_bultins_one(tools, curr, lexer);
		return (EXIT_SUCCESS);
	}
	pid = fork();
	if (pid == 0)
	{
		fill_cmd_heredoc(curr);
		dup_heredoc(curr);
		if (curr->redirections)
			if (check_redir(curr) == 1)
				exit(0);
		if (builtins_to_fork(curr) == 1)
			choose_bultins_one(tools, curr, lexer);
		else
			handle_cmd(curr, tools);
	}
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	dup_two_cmd(t_simple_cmds *curr, int pipes[2], int fd_in)
{
	if (curr->prev && dup2(fd_in, STDIN_FILENO) < 0)
	{
		perror("dup2 ");
		return (EXIT_FAILURE);
	}
	close(pipes[0]);
	if (curr->next && dup2(pipes[1], STDOUT_FILENO) < 0)
	{
		perror("dup2 ");
		return (EXIT_FAILURE);
	}
	close(pipes[1]);
	if (curr->prev)
		close(fd_in);
	return (EXIT_SUCCESS);
}

int	ft_fork(t_tools *tools, t_simple_cmds *curr, int pipes[2], int fd_in)
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
		if (dup_two_cmd(curr, pipes, fd_in) == 1)
			exit(0);
		if (curr->redirections)
			if (check_redir(curr) == 1)
				exit(0);
		if (is_builtins(curr) == 1)
			choose_bultins_multiple(tools, curr);
		else
			handle_cmd(curr, tools);
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
		if (fd_in == -1)
		{
			perror("open ");
			return (EXIT_FAILURE);
		}
	}
	else
		fd_in = pipes[0];
	return (fd_in);
}

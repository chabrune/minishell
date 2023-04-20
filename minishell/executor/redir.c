/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:30:04 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/20 18:41:40 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_append(t_lexer *redir)
{
	int fd;
	if(redir->token == GREATGREAT)
		fd = open(redir->str, O_RDWR, O_APPEND, 0644);
	else
		fd = open(redir->str, O_CREAT, O_RDWR, O_TRUNC, 0644);
	return(fd);
}

int	check_infile(char *file)
{
	int fd;
	fd = open(file, O_RDONLY);
	if(fd < 0)
		return(EXIT_FAILURE);
	if(dup2(fd, STDIN_FILENO) < 0)
		return(EXIT_FAILURE);
	if(fd >= 0)
		close(fd);
	return(EXIT_SUCCESS);
}

int check_outfile(t_lexer *redir)
{
	int fd;
	fd = check_append(redir);
	if(fd < 0)
		return(EXIT_FAILURE);
	if(dup2(fd, STDOUT_FILENO) < 0)
		return(EXIT_FAILURE);
	if(fd >= 0)
		close(fd);
	return(EXIT_SUCCESS);
}

int check_redir(t_simple_cmds *cmd)
{
	t_lexer *tmp;

	tmp = cmd->redirections;
	while(cmd->redirections)
	{
		if(cmd->redirections->token == LESS)
		{
			if(check_infile(cmd->redirections->str) == 1)
				return(EXIT_FAILURE);
		}
		else if(cmd->redirections->token == GREAT || cmd->redirections->token == GREATGREAT)
		{
			if(check_outfile(cmd->redirections) == 1)
				return(EXIT_FAILURE);
		}
		else if(cmd->redirections->token == LESSLESS)
		{
			if(check_infile(cmd->hd_file_name) == 1)
				return(EXIT_FAILURE);
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = tmp;
	return(EXIT_SUCCESS);
}
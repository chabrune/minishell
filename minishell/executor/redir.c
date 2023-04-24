/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:30:04 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/24 17:07:45 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_append(t_lexer *redir)
{
	int fd;
	if(redir->token == GREATGREAT)
	{
		fd = open(redir->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if(fd == -1)
			perror("open ");
	}
	else
	{
		fd = open(redir->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if(fd == -1)
			perror("open ");
	}
	return(fd);
}

int	check_infile(char *file, t_simple_cmds *cmd)
{
	cmd->fd = open(file, O_RDONLY);
	if(cmd->fd < 0)
	{
		perror("open ");
		return(EXIT_FAILURE);
	}
	if(dup2(cmd->fd, STDIN_FILENO) == -1)
	{
		perror("dup2 ");
		return(EXIT_FAILURE);
	}
	if(cmd->fd > 0)
		close(cmd->fd);
	return(EXIT_SUCCESS);
}

int check_outfile(t_lexer *redir, t_simple_cmds *cmd)
{
	cmd->fd = check_append(redir);
	if(cmd->fd < 0)
	{
		perror("open ");
		return(EXIT_FAILURE);
	}
	if(dup2(cmd->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 ");
		return(EXIT_FAILURE);
	}
	if(cmd->fd > 0)
		close(cmd->fd);
	return(EXIT_SUCCESS);
}

int check_redir(t_simple_cmds *cmd)
{
	t_lexer			*current;

	if (!cmd)
		return (EXIT_FAILURE);
	current = cmd->redirections;
	while(current)
	{
		if(current->token == LESS)
			check_infile(current->str, cmd);
		else if(current->token == GREAT || current->token == GREATGREAT)
			check_outfile(current, cmd);
		else if(current->token == LESSLESS)
			check_infile(cmd->hd_file_name, cmd);
		current = current->next;
	}
	return(EXIT_SUCCESS);
}

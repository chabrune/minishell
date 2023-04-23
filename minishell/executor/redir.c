/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:30:04 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/23 18:13:47 by chabrune         ###   ########.fr       */
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

int	check_infile(char *file)
{
	int fd;
	fd = open(file, O_RDONLY);
	if(fd < 0)
	{
		perror("open ");
		return(EXIT_FAILURE);
	}
	if(dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 ");
		return(EXIT_FAILURE);
	}
	if(fd > 0)
		close(fd);
	return(EXIT_SUCCESS);
}

int check_outfile(t_lexer *redir)
{
	int fd;
	fd = check_append(redir);
	if(fd < 0)
	{
		perror("open ");
		return(EXIT_FAILURE);
	}
	if(dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 ");
		return(EXIT_FAILURE);
	}
	if(fd > 0)
		close(fd);
	return(EXIT_SUCCESS);
}

int check_redir(t_simple_cmds *cmd)
{
	t_lexer			*current;
	t_simple_cmds	*tmp;

	if (!cmd)
		return (EXIT_FAILURE);
	current = cmd->redirections;
	tmp = cmd;
	while(current)
	{
		if(current->token == LESS)
			check_infile(current->str);
		else if(current->token == GREAT || current->token == GREATGREAT)
			check_outfile(current);
		else if(current->token == LESSLESS)
			check_infile(cmd->hd_file_name);
		current = current->next;
	}
	return(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:13:49 by emuller           #+#    #+#             */
/*   Updated: 2023/04/01 13:45:59 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc(char *filename)
{
	int fd;
	char *line;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("heredoc> ");
	while(line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
		close(fd);
	}
	free(line);
	close(fd);
}

char *create_filename()
{
	int i = 0;
	char *num;
	char *filename;

	num = ft_itoa(i++);
	filename = ft_strjoin(".tmp_heredocs_file_", num);
	free(num);
	return(filename);
}

void	fill_cmd_heredoc(t_simple_cmds **head)
{
	char *filename;
	t_simple_cmds *cmds;
	cmds = *head;
	if(!cmds)
		return;
	if(!cmds->redirections)
		return;
	while(cmds->redirections)
	{
		if(cmds->redirections->token == LESSLESS)
		{
			cmds->redirections = cmds->redirections->next;
			filename = create_filename();
			heredoc(filename);
		}
		cmds->redirections = cmds->redirections->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:13:49 by emuller           #+#    #+#             */
/*   Updated: 2023/03/26 17:30:28 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc(char *filename, t_simple_cmds **head)
{
	int fd;
	char *line;
	t_simple_cmds *tmp;
	tmp = *head;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	while(line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
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
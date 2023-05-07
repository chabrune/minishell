/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:13:49 by emuller           #+#    #+#             */
/*   Updated: 2023/05/07 18:32:46 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc(char *filename, t_lexer *curr)
{
	int		fd;
	char	*line;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("heredoc> ");
	if (stop_heredoc == 1)
	{
		close(fd);
		exit(0);
	}
	while (line && ft_strncmp(curr->str, line, ft_strlen(curr->str)))
	{
		if (stop_heredoc == 1)
		{
			close(fd);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(fd);
}

int	ft_whitespaces(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

char	*create_filename(void)
{
	int		i;
	char	*num;
	char	*filename;

	i = 0;
	num = ft_itoa(i++);
	filename = ft_strjoin(".tmp_heredocs_file_", num);
	free(num);
	return (filename);
}

void	fill_cmd_heredoc(t_simple_cmds *curr)
{
	char	*filename;
	t_lexer	*tmp;

	rl_catch_signals = 1;
	tmp = curr->redirections;
	if (!curr)
		return ;
	if (!curr->redirections)
		return ;
	while (curr->redirections)
	{
		if (curr->redirections->token == LESSLESS)
		{
			filename = create_filename();
			curr->hd_file_name = ft_strdup(filename);
			free(filename);
			in_heredoc = 1;
			heredoc(curr->hd_file_name, curr->redirections);
			in_heredoc = 0;
		}
		curr->redirections = curr->redirections->next;
	}
	curr->redirections = tmp;
}

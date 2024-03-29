/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:13:49 by emuller           #+#    #+#             */
/*   Updated: 2023/05/13 18:25:07 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc(char *filename, t_lexer *curr, t_tools *tools)
{
	int		fd;
	char	*line;

	signal(SIGINT, SIG_DFL);
	rl_catch_signals = 1;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("heredoc> ");
	while (line && ft_strcmp(curr->str, line))
	{
		line = expander_hd(tools, line);
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

void	fill_cmd_heredoc(t_simple_cmds *curr, t_tools *tools)
{
	char	*filename;
	t_lexer	*tmp;

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
			heredoc(curr->hd_file_name, curr->redirections, tools);
		}
		curr->redirections = curr->redirections->next;
	}
	curr->redirections = tmp;
}

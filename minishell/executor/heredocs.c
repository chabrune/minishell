/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:13:49 by emuller           #+#    #+#             */
/*   Updated: 2023/04/18 19:10:38 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	heredoc(char *filename, char *input, t_lexer *curr)
{
	int		fd;
	char	*line;
	char	*delimit;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	delimit = get_word_after_hd(input);
	line = readline("heredoc> ");
	while (line && ft_strncmp(curr->str, line, ft_strlen(curr->str)))
	{
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

char	*get_word_after_hd(char *line)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	res = NULL;
	k = 0;
	j = 0;
	i = 0;
	while (line[i] && line[i] != '<')
		i++;
	if (line[i] && line[i + 1] == '<')
	{
		i += 2;
		while (line[i] && ft_whitespaces(line[i]))
			i++;
		while (line[i++] && !ft_whitespaces(line[i]))
			j++;
		i = i - j - 1;
		res = ft_calloc(sizeof(char), j + 1);
		while (j > 0)
		{
			res[k++] = line[i++];
			j--;
		}
	}
	return (res);
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

void	fill_cmd_heredoc(t_simple_cmds *curr, char *input)
{
	char *filename;

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
			heredoc(curr->hd_file_name, input, curr->redirections);
		}
		curr->redirections = curr->redirections->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:53:31 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/13 10:43:55 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*fill_buffer_word(int *i, char *input, t_tokens *token)
{
	int		j;
	int		len;
	char	*buffer;

	j = 0;
	fill_buffer_word_two(input, i, &j);
	buffer = ft_calloc(j + 1, sizeof(char));
	*i = *i - j;
	len = j;
	j = 0;
	while (len > 0)
	{
		buffer[j++] = input[(*i)++];
		len--;
	}
	*token = WORD;
	return (buffer);
}

void	fill_buffer_word_two(char *input, int *i, int *j)
{
	while (input[*i])
	{
		if (input[*i] == '\"')
		{
			(*i)++;
			*j += 1;
			while (input[*i] && input[*i] != '\"')
			{
				(*i)++;
				*j += 1;
			}
		}
		if (ft_isspace(input[*i]) || ft_istoken(input[*i]))
			break ;
		(*i)++;
		*j += 1;
	}
}

char	*fill_buffer_meta(int *i, char *input, t_tokens *token)
{
	int		j;
	char	*buffer;

	j = 0;
	while (input[*i] && ft_istoken(input[*i]) == 1)
	{
		j++;
		(*i)++;
	}
	buffer = ft_calloc(j + 1, sizeof(char));
	*i = *i - j;
	j = 0;
	while (input[*i] && ft_istoken(input[*i]) == 1)
		buffer[j++] = input[(*i)++];
	*token = chose_token(buffer);
	if (*token == 0)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		g_global.error_num = 258;
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

t_lexer	*create_token(char *input, int *i, t_tools *tools)
{
	char		*buffer;
	t_tokens	token;

	if (input[*i] == '\'')
		buffer = fill_buffer_quote(i, input, '\'', &token);
	else if (input[*i] == '\"')
		buffer = fill_buffer_quote(i, input, '\"', &token);
	else if (ft_istoken(input[*i]) == 0)
		buffer = fill_buffer_word(i, input, &token);
	else
	{
		buffer = fill_buffer_meta(i, input, &token);
		if (!buffer)
			return (NULL);
	}
	return (new_token(buffer, token, tools->k++));
}

void	add_token(t_lexer **head, t_lexer **tail, t_lexer *new)
{
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		(*tail)->prev = *tail;
		*tail = new;
	}
}

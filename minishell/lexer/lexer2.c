/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:53:31 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/07 17:42:40 by chabrune         ###   ########.fr       */
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
		ft_putendl_fd("bash: syntax error", 2);
		error_num = 258;
	}
	return (buffer);
}

// IL FAUT ENCORE GERER LES QUOTES NON FERMEES !!!
t_lexer	*ft_lexer(char *input, t_tools *tools)
{
	t_lexer		*head;
	t_lexer		*tail;
	t_lexer		*new;
	t_tokens	token;
	char		*buffer;
	int			i;
	int			k;

	head = 0;
	tail = 0;
	i = 0;
	k = 1;
	input = expander(tools, input);
	if (!input)
		return (NULL);
	while (input[i])
	{
		while (ft_isspace(input[i]) && input[i])
			i++;
		if (input[i] == '\'')
			buffer = fill_buffer_quote(&i, input, '\'', &token);
		else if (input[i] == '\"')
			buffer = fill_buffer_quote(&i, input, '\"', &token);
		else if (ft_istoken(input[i]) == 0)
			buffer = fill_buffer_word(&i, input, &token);
		else
			buffer = fill_buffer_meta(&i, input, &token);
		while (ft_isspace(input[i]) && input[i])
			i++;
		new = new_token(ft_strdup(buffer), token, k++);
		if (head == NULL)
		{
			head = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail->prev = tail;
			tail = new;
		}
			free(buffer);
		}
	return (head);
}

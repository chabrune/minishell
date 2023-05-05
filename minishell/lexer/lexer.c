/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:19:44 by emuller           #+#    #+#             */
/*   Updated: 2023/05/06 00:52:00 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*new_token(char *str, t_tokens token, int i)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->token = token;
	new->i = i;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v')
		return (1);
	else
		return (0);
}

int	ft_istoken(int c)
{
	if (!c)
		return (0);
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}

t_tokens	chose_token(char *str)
{
	t_tokens	token;

	token = 0;
	if (ft_strncmp(str, "|", 2) == 0)
		token = PIPE;
	else if (ft_strncmp(str, "<", 2) == 0)
		token = LESS;
	else if (ft_strncmp(str, "<<", 3) == 0)
		token = LESSLESS;
	else if (ft_strncmp(str, ">", 2) == 0)
		token = GREAT;
	else if (ft_strncmp(str, ">>", 3) == 0)
		token = GREATGREAT;
	return (token);
}

char	*fill_buffer_quote(int *i, char *input, int c, t_tokens *token)
{
	int		j;
	char	*buffer;

	(*i)++;
	j = 0;
	while (input[*i] && input[*i] != c)
	{
		j++;
		(*i)++;
	}
	buffer = ft_calloc(j + 1, sizeof(char));
	*i = *i - j;
	j = 0;
	while (input[*i] && input[*i] != c)
		buffer[j++] = input[(*i)++];
	(*i)++;
	*token = WORD;
	return (buffer);
}
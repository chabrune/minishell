/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:19:44 by emuller           #+#    #+#             */
/*   Updated: 2023/05/06 15:51:19 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*new_token(char *str, t_tokens token, int i)
{
	t_lexer	*new;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = str;
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
	{
		token = GREATGREAT;
	}
	return (token);
}

char *fill_buffer_quote(int *i, char *input, int c, t_tokens *token)
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

char	*fill_buffer_word(int *i, char *input, t_tokens *token)
{
	int		j;
	int		len;
	char	*buffer;

	j = 0;
	while (input[*i])
	{
		if (input[*i] == '\"')
		{
			(*i)++;
			j++;
			while (input[*i] && input[*i] != '\"')
			{
				(*i)++;
				j++;
			}
		}
		if (ft_isspace(input[*i]) || ft_istoken(input[*i]))
			break ;
		(*i)++;
		j++;
	}
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

// void	check_token(t_lexer *lexer)
// {
// 	t_lexer *tmp;
// 	int i;

// 	tmp = lexer;
// 	i = 0;
// 	while(tmp)
// 	{
// 		if (tmp->token == GREAT || tmp->token == GREATGREAT || tmp->str == LESS || tmp->str == ' ')
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	if(i == tmp->i)
// 	{
// 		ft_putendl_fd("bash: syntax error", 2)
// 		error_num = 258;
// 	}
// }

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
			new->prev = tail;
			tail = new;
		}
		free(buffer);
	}
	// check_token(head);
	return (head);
}

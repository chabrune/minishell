/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:36:16 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/12 22:17:39 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_pipe(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (!tmp)
		return (0);
	if (tmp->token == PIPE)
	{
		g_global.error_num = 258;
		ft_putendl_fd("bash: syntax erreur", 2);
		return (1);
	}
	while (tmp)
	{
		if (tmp->token == PIPE && tmp->next == NULL)
		{
			g_global.error_num = 258;
			ft_putendl_fd("bash: syntax erreur", 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_lexer	*ft_lexer(char *input, t_tools *tools)
{
	t_lexer	*head;
	t_lexer	*tail;
	int		i;
	t_lexer	*new;

	tail = NULL;
	head = NULL;
	i = 0;
	input = expander(tools, input);
	if (!input)
		return (NULL);
	while (input[i])
	{
		while (ft_isspace(input[i]) && input[i])
			i++;
		new = create_token(input, &i, tools);
		if (!new)
			return (NULL);
		while (ft_isspace(input[i]) && input[i])
			i++;
		add_token(&head, &tail, new);
		free(new->buffer);
	}
	free(input);
	return (head);
}

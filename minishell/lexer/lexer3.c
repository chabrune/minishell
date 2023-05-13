/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:36:16 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/13 20:51:56 by chabrune         ###   ########.fr       */
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

t_lexer	*ft_lexer(t_tools *tools)
{
	t_lexer	*head;
	t_lexer	*tail;
	int		i;
	t_lexer	*new;

	tail = NULL;
	head = NULL;
	i = 0;
	tools->input_copy = expander(tools, tools->input_copy);
	if (!tools->input_copy)
		return (NULL);
	while (tools->input_copy[i])
	{
		while (ft_isspace(tools->input_copy[i]) && tools->input_copy[i])
			i++;
		new = create_token(tools->input_copy, &i, tools);
		if (!new)
		{
			lstclear_lexer(&head, free);
			lstclear_lexer(&tail, free);
			free(tools->input_copy);
			tools->input_copy = NULL;
			return NULL;
		}
		while (ft_isspace(tools->input_copy[i]) && tools->input_copy[i])
			i++;
		add_token(&head, &tail, new);
	}
	free(tools->input_copy);
	tools->input_copy = NULL;
	return (head);
}

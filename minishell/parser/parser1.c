/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/06 01:02:00 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple_cmds	*group_command(t_lexer **lexer)
{
	t_lexer			*tmp;
	t_simple_cmds	*head;
	t_simple_cmds	*new;
	t_lexer			*prev;

	head = NULL;
	new = NULL;
	tmp = *lexer;
	prev = NULL;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			new = new_node();
			add_back(&head, new);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev && prev->token != PIPE)
	{
		new = new_node();
		add_back(&head, new);
	}
	return (head);
}

void	ft_lstdelone_lexer(t_lexer *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del)
		del(lst->str);
	free(lst);
}

void	del_node(t_lexer **head, t_lexer *node_to_delete)
{
	t_lexer	*current;

	if (!head || !*head || !node_to_delete)
		return ;
	if (*head == node_to_delete)
	{
		*head = node_to_delete->next;
		free(node_to_delete->str);
		free(node_to_delete);
		return ;
	}
	current = *head;
	while (current && current->next != node_to_delete)
		current = current->next;
	if (!current)
		return ;
	current->next = node_to_delete->next;
	free(node_to_delete->str);
	free(node_to_delete);
}

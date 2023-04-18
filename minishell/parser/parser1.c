
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/13 17:10:26 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// creer la liste chainee des commandes
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

void	print_t_lexer_list(t_simple_cmds *head)
{
	t_lexer			*current;
	t_simple_cmds	*tmp;

	if (!head)
		return ;
	current = head->redirections;
	tmp = head;
	while (tmp)
	{
		while (current)
		{
			printf("Token: %d, Filename: %s\n", current->token, current->str);
			current = current->next;
		}
		tmp = tmp->next;
	}
}

void	ft_lstdelone_lexer(t_lexer *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del)
		del(lst->str);
	free(lst);
}

void	del_node(t_lexer **head, t_lexer *delone)
{
	if (!head)
		return ;
	if (*head == delone) // si le noeud à supprimer est la tête de la liste
		*head = delone;
	if (delone && delone->prev != NULL) // si le noeud à supprimer n'est pas la tête de la liste
		delone->prev->next = delone->next;
	if (delone && delone->next != NULL) // si le noeud à supprimer n'est pas la queue de la liste
		delone->next->prev = delone->prev;
	free(delone);
	delone = NULL;
}



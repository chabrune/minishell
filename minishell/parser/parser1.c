
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

//rempli le **str de simple cmd
char	**lexer_to_str_array(t_lexer *curr, t_lexer *stop, int *redir, t_lexer **head)
{
	t_lexer	*tmp;
	char	**arr;
	int		len;
	int		i;

	i = 0;
	len = 0;
	tmp = *head;
	while (tmp && tmp != stop)
	{
		len++;
		tmp = tmp->next;
	}
	arr = ft_calloc(sizeof(char *), (len + 1));
	tmp = curr;
	while (tmp && (tmp != stop || stop == NULL))
	{
		if (tmp->token == GREAT || tmp->token == LESS
			|| tmp->token == GREATGREAT || tmp->token == LESSLESS)
			*redir += 1;
		arr[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

// creer la liste chainee des commandes
t_simple_cmds	*group_command(t_lexer **lexer)
{
	t_lexer			*tmp;
	t_simple_cmds	*head;
	t_simple_cmds	*new;
	t_lexer			*tmp1;
	t_lexer			*prev;

	head = NULL;
	new = NULL;
	tmp = *lexer;
	tmp1 = *lexer;
	prev = NULL;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			new = new_node();
			new->str = lexer_to_str_array(tmp1, tmp, &(new->num_redirections), lexer);
			add_back(&head, new);
			tmp1 = tmp->next;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev && prev->token != PIPE)
	{
		new = new_node();
		new->str = lexer_to_str_array(tmp1, NULL, &(new->num_redirections), lexer);
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

void	del_node(t_lexer **head, t_lexer *delone)
{
	if (!head)
		return ;
	if (*head == delone) // si le noeud à supprimer est la tête de la liste
		*head = delone->next;
	if (delone && delone->prev != NULL)
	// si le noeud à supprimer n'est pas la tête de la liste
		delone->prev->next = delone->next;
	if (delone && delone->next != NULL)
	// si le noeud à supprimer n'est pas la queue de la liste
		delone->next->prev = delone->prev;
	free(delone);
	delone = NULL;
}

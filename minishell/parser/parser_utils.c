/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:08:43 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/06 17:49:17 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple_cmds	*new_node(void)
{
	t_simple_cmds	*new;

	new = ft_calloc(1, sizeof(t_simple_cmds));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->redirections = NULL;
	new->num_redirections = 0;
	new->str = NULL;
	return (new);
}

void	add_back(t_simple_cmds **head, t_simple_cmds *new)
{
	t_simple_cmds	*tmp;

	if (!head || !new) // si head n'existe pas
		return ;
	new->next = NULL;
	if (!*head) // si *head est vide (si la chaine est vide)
	{
		new->prev = NULL;
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	print_cmd(t_simple_cmds **head)
{
	t_simple_cmds	*tmp;
	int				i;

	if (!head)
		return ;
	tmp = *head;
	if(!tmp)
		return ;
	while (tmp)
	{
		if(tmp->str)
		{
			i = 0;
			while (tmp->str[i])
			{
				printf("cmd == %s\n", tmp->str[i]);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

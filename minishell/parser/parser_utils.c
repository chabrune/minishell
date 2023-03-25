/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:08:43 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/25 16:27:50 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple_cmds    *new_node()
{
    t_simple_cmds *new;
    new = ft_calloc(1, sizeof(t_simple_cmds));
    if(!new)
        return(NULL);
    new->next = NULL;
    new->prev = NULL;
	new->redirections = NULL;
	new->num_redirections = 0;
	new->str = NULL;
    return(new);
}

void    add_back(t_simple_cmds **head, t_simple_cmds *new)
{
    if (!head || !new) // si head n'existe pas
        return ;
    new->next = NULL;
    if (!*head) // si *head est vide (si la chaine est vide)
    {
        new->prev = NULL;
        *head = new;
        return ;
    }
    t_simple_cmds  *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}

void print_cmd(t_simple_cmds **head)
{
    if(!head)
        return;
    t_simple_cmds *tmp;
    int i;
    tmp = *head;
    while (tmp != NULL) 
    {
        i = 0;
        while(tmp->str[i])
        {
			if(i == 0)
				printf("cmd : ");
            printf("%s ", tmp->str[i]);
            i++;
        }
        printf("\n");
        tmp = tmp->next;
    }
}

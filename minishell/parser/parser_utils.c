/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:08:43 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/12 16:23:33 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	cmp(int token, int data_ref)
{
	if (token == data_ref)
		return (0);
	return (1);
}

void ft_list_remove_if(t_lexer **begin_list, int data_ref, int (*cmp)(int, int))
{
    if (!begin_list || !*begin_list)
        return;
    t_lexer *cur = *begin_list;
    t_lexer *prev = NULL;
    while (cur != NULL)
    {
        if (cmp(cur->token, data_ref) == 0)
        {
            if (prev == NULL)
                *begin_list = cur->next;
            else
                prev->next = cur->next;

            t_lexer *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

t_simple_cmds    *new_node()
{
    t_simple_cmds *new;
    new = malloc(sizeof(t_simple_cmds));
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

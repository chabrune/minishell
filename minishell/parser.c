/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/05 01:57:52 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmds *new_node()
{
    t_simple_cmds *new;
    new = malloc(sizeof(t_simple_cmds));
    if(!new)
        return(NULL);
    new->next = NULL;
    new->prev = NULL;
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

char **lexer_to_str_array(t_lexer **head, t_lexer *stop)
{
    t_lexer *tmp;
    char **arr;
    int len;
    int i;

    i = 0;
    len = 0;
    tmp = *head;
    while(tmp && tmp != stop)
    {
        len++;
        tmp = tmp->next;
    }
    arr = malloc(sizeof(char*) * len);
    tmp = *head;
    while(i < len && tmp && tmp != stop)
    {
        arr[i] = ft_strdup(tmp->str);
        tmp = tmp->next;
        i++;
    }
    // arr[i] = NULL;
    return(arr);
}

void print_cmd(t_simple_cmds **head)
{
    t_simple_cmds *tmp;
    tmp = *head;
    while (tmp)
    {
        int i = 0;
        while (tmp->str[i])
        {
            printf("%s\n", tmp->str[i]);
            i++;
        }
        tmp = tmp->next;
    }
}


t_simple_cmds *group_command(t_lexer **lexer)
{
    t_lexer *tmp;
    t_simple_cmds *head;
    t_simple_cmds *new;

    head = NULL;
    tmp = *lexer;
    while(tmp)
    {
        if(tmp->token == PIPE)
        {
            new = new_node();
            new->str = lexer_to_str_array(lexer, tmp);
            add_back(&head, new);
            *lexer = tmp->next;
            tmp = tmp->next;
        }
        else
            tmp = tmp->next;
    }
    // if(!new)
    //     new = new_node();
    // new->str = lexer_to_str_array(lexer, tmp);
    // add_back(&head, new);
    print_cmd(&head);
    return(head);
}

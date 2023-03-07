/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/07 16:07:30 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmds    *new_node()
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

char **lexer_to_str_array(t_lexer *curr, t_lexer *stop)
{
    t_lexer *tmp;
    char **arr;
    int len;
    int i;

    i = 0;
    len = 0;
    tmp = curr;
    while(tmp && tmp != stop)
    {
        len++;
        tmp = tmp->next;
    }
    arr = malloc(sizeof(char*) * (len + 1));
    tmp = curr;
    while(i < len && tmp && tmp != stop)
    {
        arr[i] = ft_strdup(tmp->str);
        tmp = tmp->next;
        i++;
    }
    arr[i] = NULL;
    return(arr);
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
            printf("%s ", tmp->str[i]);
            i++;
        }
        printf("\n");
        tmp = tmp->next;
    }
}

t_simple_cmds *group_command(t_lexer **lexer)
{
    t_lexer *tmp;
    t_simple_cmds *head;
    t_simple_cmds *new;
    t_lexer *tmp1;

    head = NULL;
    new = NULL;
    tmp = *lexer;
    tmp1 = *lexer;
    while(tmp && tmp->next)
    {
        if(tmp->token == PIPE)
        {
            new = new_node();
            new->str = lexer_to_str_array(tmp1, tmp);
            add_back(&head, new);
            tmp1 = tmp->next;
            tmp = tmp->next;

        }
        else
            tmp = tmp->next;
    }
    if(!new)
    {
        tmp1 = *lexer;
        new = new_node();
        new->str = lexer_to_str_array(tmp1, NULL);
        add_back(&head, new);
    }
    print_cmd(&head);
    return(head);
}

void    find_redir(t_simple_cmds **head, t_lexer **lexer)
{
    t_lexer *tmp;
    tmp = *lexer;
    int i = 0;
    int j;
    while(tmp)
    {
        if(tmp->token == GREAT || tmp->token == GREATGREAT)
        
        else if(tmp->token == LESS || tmp->token == LESSLESS)

        

    }
}

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
char **lexer_to_str_array(t_lexer *curr, t_lexer *stop, int *redir)
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
    while (tmp && (tmp != stop || stop == NULL))
    {
		if(tmp->token == GREAT || tmp->token == LESS || tmp->token == GREATGREAT || tmp->token == LESSLESS)
			*redir += 1;
        arr[i] = ft_strdup(tmp->str);
        tmp = tmp->next;
        i++;
    }
    arr[i] = NULL;
    return(arr);
}

// creer la liste chainee des commandes
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
    t_lexer *prev = NULL;
    while (tmp)
    {
        if (tmp->token == PIPE)
        {
            new = new_node();
            new->str = lexer_to_str_array(tmp1, tmp, &(new->num_redirections));
            add_back(&head, new);
            tmp1 = tmp->next;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if (prev && prev->token != PIPE)
    {
        new = new_node();
        new->str = lexer_to_str_array(tmp1, NULL, &(new->num_redirections));
        add_back(&head, new);
    }
    print_cmd(&head);
    return head;
}

void print_t_lexer_list(t_simple_cmds *head)
{
    if(!head)
        return;
    t_lexer *current = head->redirections;
    t_simple_cmds *tmp = head;

    while(tmp)
    {
        while (current)
        {
            printf("Token: %d, Filename: %s\n", current->token, current->str);
            current = current->next;
        }
        tmp = tmp->next;
    }
}

void    del_node(t_lexer **head, t_lexer *delone)
{
    if(*head == delone) // si le noeud à supprimer est la tête de la liste
        *head = delone->next;
    if(delone->prev != NULL)  // si le noeud à supprimer n'est pas la tête de la liste
        delone->prev->next = delone->next;
    if(delone->next != NULL) // si le noeud à supprimer n'est pas la queue de la liste
        delone->next->prev = delone->prev;
    free(delone);
}

void    last_lexer_to_strs_cmd(t_lexer **headlex, t_simple_cmds **headcmd)
{
    t_lexer *tmplex;
    t_simple_cmds *tmpcmd;
    tmplex = *headlex;
    tmpcmd = *headcmd;
    int i;

    i = 0;
    while(tmpcmd)
    {
        if(tmplex->token == PIPE)
            tmplex = tmplex->next;
        while(tmplex && tmplex->token != PIPE)
        {
            tmpcmd->str[i] = tmplex->str;
            printf("rest of lexer : %s\n", tmpcmd->str[i]);
            tmplex = tmplex->next;
            i++;
        }
        tmpcmd = tmpcmd->next;
    }
}

t_lexer *init_redir_next(t_lexer *curr)
{
    t_lexer *redir;
    redir = malloc(sizeof(t_lexer));
    if(!redir)
        return(NULL);
    redir->token = curr->token;
    redir->str = ft_strdup(curr->next->str);
    redir->next = NULL;
    return(redir);
}

t_lexer *init_redir_prev(t_lexer *curr)
{
    t_lexer *redir;
    redir = malloc(sizeof(t_lexer));
    if(!redir)
        return(NULL);
    redir->token = curr->token;
    redir->str = ft_strdup(curr->prev->str);
    redir->next = NULL;
    return(redir);
}

void    add_node_redir(t_simple_cmds *curr, t_lexer *redir)
{
    t_lexer *tmp_redir = NULL;
    if(!curr->redirections)
        curr->redirections = redir;
    else
    {
        if(!tmp_redir)
        {
            tmp_redir = curr->redirections;
            while(tmp_redir->next)
                tmp_redir = tmp_redir->next;
        }
        tmp_redir->next = redir;
        redir->prev = tmp_redir;
        tmp_redir = redir;
    }
}

void    add_redir_if_great(t_simple_cmds **head, t_lexer **lexer)
{
    t_simple_cmds *tmpcmd = *head;
    t_lexer *tmplex = *lexer;
    t_lexer *redir;
    while (tmpcmd)
    {
        if(tmplex->token == PIPE)
            tmplex = tmplex->next;
        while(tmplex && tmplex->token != PIPE)
        {
            if(tmplex->token == GREAT || tmplex->token == GREATGREAT)
            {
                redir = init_redir_next(tmplex);
                add_node_redir(tmpcmd, redir);
                del_node(lexer, tmplex->next);
                del_node(lexer, tmplex);
            }
            tmplex = tmplex->next;
        }
        tmpcmd = tmpcmd->next;
    }
}

void    add_redir_if_less(t_simple_cmds **head, t_lexer **lexer)
{
    t_simple_cmds *tmpcmd = *head;
    t_lexer *tmplex = *lexer;
    t_lexer *redir;
    while (tmpcmd)
    {
        if(tmplex->token == PIPE)
            tmplex = tmplex->next;
        while(tmplex && tmplex->token != PIPE)
        {
            if(tmplex->token == LESS || tmplex->token == LESSLESS)
            {
                redir = init_redir_prev(tmplex);
                add_node_redir(tmpcmd, redir);
                del_node(lexer, tmplex->prev);
                del_node(lexer, tmplex);
            }
            tmplex = tmplex->next;
        }
        tmpcmd = tmpcmd->next;
    }
}

void    find_redir(t_simple_cmds **head, t_lexer **lexer)
{
    add_redir_if_great(head, lexer);
    add_redir_if_less(head, lexer);
    last_lexer_to_strs_cmd(lexer, head);
}
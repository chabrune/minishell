/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/13 13:57:18 by chabrune         ###   ########.fr       */
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
    t_lexer *current = head->redirections;
    t_simple_cmds *tmp = head;

    while(tmp)
    {
        while (head->redirections)
        {
            printf("Token: %d, Filename: %s\n", current->token, current->str);
            head->redirections = head->redirections->next;
        }
        tmp = tmp->next;
    }
}

void find_redir(t_simple_cmds **head, t_lexer **lexer)
{
    t_simple_cmds *tmpcmd = *head;
    t_lexer *tmplex = *lexer;
    t_lexer *redir;
    t_lexer *tmp_redir;
    while (tmpcmd)
    {
        tmp_redir = NULL;
        while(tmplex && tmplex->token != PIPE)
        {
            if(tmplex->token == GREAT || tmplex->token == GREATGREAT)
            {
                redir = malloc(sizeof(t_lexer));
                if(!redir)
                    return;
                redir->token = tmplex->token;
                redir->str = ft_strdup(tmplex->next->str);
                redir->next = NULL;
                if(!tmpcmd->redirections)
                    tmpcmd->redirections = redir;
                else
                {
                    if(!tmp_redir)
                    {
                        tmp_redir = tmpcmd->redirections;
                        while(tmp_redir->next)
                            tmp_redir = tmp_redir->next;
                    }
                    tmp_redir->next = redir;
                    redir->prev = tmp_redir;
                    tmp_redir = redir;
                }
                // tmpcmd->redirections = tmpcmd->redirections->next;
                // lstdelone_lexer(tmplex->next, free);
                // lstdelone_lexer(tmplex, free);
                // tmplex->prev = tmplex->next->next;
            }
            else if (tmplex->token == LESS || tmplex->token == LESSLESS)
            {
                redir = malloc(sizeof(t_lexer));
                if(!redir)
                    return;
                redir->token = tmplex->token;
                redir->str = ft_strdup(tmplex->prev->str);
                redir->next = NULL;
                if(!tmpcmd->redirections)
                    tmpcmd->redirections = redir;
                else
                {
                    if(!tmp_redir)
                    {
                        tmp_redir = tmpcmd->redirections;
                        while(tmp_redir->next)
                            tmp_redir = tmp_redir->next;
                    }
                    tmp_redir->next = redir;
                    redir->prev = tmp_redir;
                    tmp_redir = redir;
                }
                // tmpcmd->redirections = tmpcmd->redirections->next;
                // lstdelone_lexer(tmplex->prev, free);
                // lstdelone_lexer(tmplex, free);
                // tmplex->prev->prev = tmplex->next;
            }
            tmplex = tmplex->next;
        }
        tmpcmd = tmpcmd->next;
    }
}

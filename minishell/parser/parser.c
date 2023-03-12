/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/12 17:51:32 by chabrune         ###   ########.fr       */
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
            printf("coucou\n");
            printf("Token: %d, Filename: %s\n", current->token, current->str);
            head->redirections = head->redirections->next;
        }
        tmp = tmp->next;
    }
}

// malloc le nombre de redirection
// a voir si c'est utile
void add_redir_to_cmd(t_simple_cmds *head, int num_redirections)
{
    int i;

    i = -1;
    while(++i < num_redirections)
    {
        t_lexer *new_redir = malloc(sizeof(t_lexer));
        if(!new_redir)
            return;
        new_redir->next = NULL;
        new_redir->prev = NULL;
        if(head->redirections == NULL)   // si il n'y a pas encore de redir
            head->redirections = new_redir;
        else
        {
            t_lexer *tmp_redir = head->redirections; 
            while(tmp_redir->next != NULL) // on va a la fin de la liste chainee
                tmp_redir = tmp_redir->next;
            tmp_redir->next = new_redir; // on ajoute la nouvelle redir
        }
    }
}


void find_redir(t_simple_cmds **head, t_lexer **lexer)
{
    t_simple_cmds *tmpcmd = *head;
    t_lexer *tmplex = *lexer;
    //t_lexer *prevlex = NULL;

    while (tmpcmd)
    {
        add_redir_to_cmd(tmpcmd, tmpcmd->num_redirections);
        while(tmplex && tmplex->token != PIPE)
        {
            if(tmplex->token == GREAT || tmplex->token == GREATGREAT)
            {
                tmpcmd->redirections->token = tmplex->token;
                tmpcmd->redirections->str = ft_strdup(tmplex->next->str);
                tmpcmd->redirections = tmpcmd->redirections->next;
            }
            else if (tmplex->token == LESS || tmplex->token == LESSLESS)
            {
                tmpcmd->redirections->token = tmplex->token;
                tmpcmd->redirections->str = ft_strdup(tmplex->prev->str);
                tmpcmd->redirections = tmpcmd->redirections->next;
            }
            printf("%s\n", tmpcmd->redirections->str);
            printf("%d\n", tmpcmd->redirections->token);
            tmplex = tmplex->next;
            //if (tmplex->token == PIPE && tmplex)
            //    tmplex = tmplex->next;
        }
        tmpcmd = tmpcmd->next;
    }
}

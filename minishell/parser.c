/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/05 13:47:49 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void find_redir(t_simple_cmds **head, t_lexer **lexer)
{
    t_lexer *tmplex = *lexer;
    t_simple_cmds *tmpcmd = *head;
    while (tmpcmd != NULL)
    {
        while (tmplex && tmplex->token != PIPE)
        {
            if (tmplex->token == GREATGREAT)
            {
				if(!tmpcmd->redirections)

                tmpcmd->redirections->token = GREATGREAT;
                ft_list_remove_if(lexer, GREATGREAT, &cmp);
                tmpcmd->redirections = NULL;  
				tmplex = *lexer;
            }
			else if (tmplex->token == GREAT)
            {
                tmpcmd->redirections->token = GREAT;
                ft_list_remove_if(lexer, GREAT, &cmp);
                tmpcmd->redirections = NULL;
				tmplex = *lexer;
            }
            else if (tmplex->token == LESS)
            {
                tmpcmd->redirections->token = LESS;
                ft_list_remove_if(lexer, LESS, &cmp);
                tmpcmd->redirections = NULL;
				tmplex = *lexer;
            }
            else if (tmplex->token == LESSLESS)
            {
                tmpcmd->redirections->token = LESSLESS;
                ft_list_remove_if(lexer, LESSLESS, &cmp);
                tmpcmd->redirections = NULL;
				tmplex = *lexer;
            }
            tmplex = tmplex->next;
        }
        tmpcmd = tmpcmd->next;
    }
}
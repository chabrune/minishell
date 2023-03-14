/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:16:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/14 16:41:39 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    add_redir_if_less(t_simple_cmds **head, t_lexer **lexer)
{
    t_simple_cmds *tmpcmd = *head;
    t_lexer *tmplex = *lexer;
    t_lexer *redir;
    while (tmpcmd)
    {
        if(tmplex->token == PIPE)
            tmplex = tmplex->next;
        while(tmplex && tmplex->token != PIPE && tmplex->next)
        {
            if(tmplex->token == LESS || tmplex->token == LESSLESS)
            {
                redir = init_redir_prev(tmplex);
                add_node_redir(tmpcmd, redir);
                del_node(lexer, tmplex->prev);
                del_node(lexer, tmplex);
                tmplex = *lexer;
            }
            else
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

int count_cmd(t_simple_cmds **head)
{
	t_simple_cmds *tmp;
    int i;

    i = 0;
    tmp = *head;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    return(i);
}

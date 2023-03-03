/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/03 12:51:46 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **lexer_to_str_array(t_lexer *lexer, t_lexer *stop)
{
    int len;
    char **arr;
    t_lexer *curr;
    int i;

    i = 0;
    curr = lexer;
    while(curr && curr != stop)
    {
        len++;
        curr = curr->next;
    }
    arr = ft_calloc(sizeof(char *), len + 1);
    curr = lexer;
    while(i < len && curr && curr != stop)
    {
        arr[i] = ft_strdup(curr->str);
        curr = curr->next;
        i++;
    }
    return(arr);
}


t_simple_cmds	*parser(t_lexer *lexer)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*curr_cmd;
	t_lexer			*curr_lexer;

    curr_lexer = lexer;
    while(curr_lexer)
    {
        if(curr_lexer->token == PIPE)
        {
            if(!curr_cmd)
                curr_cmd = ft_calloc(1, sizeof(t_simple_cmds));
            curr_cmd->str = lexer_to_str_array(lexer, curr_lexer);
            if(cmds)
                cmds->prev = curr_cmd;
			curr_cmd->next = cmds;
			cmds = curr_cmd;
			curr_cmd = NULL;
			lexer = curr_lexer->next;
			curr_lexer = curr_lexer->next;
        }
    }
}
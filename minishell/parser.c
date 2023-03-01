/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/01 06:23:53 by chabrune         ###   ########.fr       */
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


t_simple_cmds	*group_command(t_lexer *lexer)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*curr_cmd;
	t_lexer			*curr_lexer;

    cmds = NULL;
    curr_cmd = NULL;
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
        else
            curr_lexer = curr_lexer->next;
    }
    if(!curr_cmd)
        curr_cmd = ft_calloc(sizeof(t_simple_cmds), 1);
    curr_cmd->str = lexer_to_str_array(lexer, NULL);
    if(cmds)
        cmds->prev = curr_cmd;
    curr_cmd->next = cmds;
    cmds = curr_cmd;
    return(cmds);
}

void print_cmds(t_simple_cmds *cmds) 
{
    int i = 1;
    int j;
    while (cmds) 
    {
        printf("Cmd %d: ", i);
        char **str_arr = cmds->str;
        j = 0;
        while(str_arr[j]) 
        {
            printf("%s ", str_arr[j]);
            j++;
        }
        printf("\n");
        cmds = cmds->next;
        i++;
    }
}

// t_simple_cmds	*ft_parse(t_lexer *lexer)
// {

// }
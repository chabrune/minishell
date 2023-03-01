/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:47:39 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/01 07:43:19 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Converti les elements (str) de la liste chainee lexer en char ** si pipe il y a
// Sinon regroupe tout les noeuds dans le char **

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

// regroupe les commandes séparées par des pipes en créant de nouveaux éléments de type t_simple_cmds

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

// print chaque cmd 

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

// Parcours la liste t_simple_cmds retourne par group_command() et verifie si redirection / builtin 

t_simple_cmds	*ft_parse(t_lexer *lexer)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*curr_cmd;
	t_lexer			*curr_lexer;

	cmds = group_command(lexer);
	curr_cmd = cmds;
	while (curr_cmd)
	{
		// Check for redirections and store in redirections list
		curr_lexer = curr_cmd->str;
		while (curr_lexer)
		{
			if (is_redirection(curr_lexer->token))
			{
				curr_cmd->redirections = lexer_add_node(curr_cmd->redirections, curr_lexer->token, curr_lexer->next->str);
				curr_lexer = lexer_remove_node(curr_lexer);
				curr_lexer = lexer_remove_node(curr_lexer);
			}
			else
				curr_lexer = curr_lexer->next;
		}
		// Check for builtin command
		if (curr_cmd->str && is_builtin(curr_cmd->str[0]))
			curr_cmd->builtin = get_builtin_func(curr_cmd->str[0]);

		// Combine remaining words into 2D array
		curr_cmd->str = lexer_to_str_array(curr_lexer, NULL);

		curr_cmd = curr_cmd->next;
	}

	return (cmds);
}


int is_redirection(t_lexer *lexer) 
{
	if(lexer->token >= 3 && lexer->token <= 6)
		return(1);
	return(0);
}

int is_builtin(char *cmd)
{
	if(!ft_strncmp(cmd, "echo", 5))
		return(1);
	else if(!ft_strncmp(cmd, "cd", 3))
		return(1);
	else if(!ft_strncmp(cmd, "pwd", 4))
		return(1);
	else if(!ft_strncmp(cmd, "export", 7))
		return(1);
	else if(!ft_strncmp(cmd, "unset", 6))
		return(1);
	else if(!ft_strncmp(cmd, "env", 4))
		return(1);
	else if(!ft_strncmp(cmd, "exit", 5))
		return(1);
	return(0);
}
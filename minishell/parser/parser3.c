/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:16:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 13:23:22 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_cmd(t_simple_cmds **head)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	add_redir_splitted(t_simple_cmds *tmpcmd, t_lexer **tmplex,
		t_lexer **redir, t_lexer **lexer)
{
	tmpcmd->num_redirections++;
	*redir = init_redir(*tmplex);
	add_node_redir(tmpcmd, *redir);
	if ((*tmplex)->next)
		del_node(lexer, (*tmplex)->next);
	del_node(lexer, *tmplex);
	*tmplex = *lexer;
}

int	count_t_lexer(t_lexer *curr)
{
	int	i;

	i = 0;
	while (curr && curr->token != PIPE)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

void	last_lexer_to_strs_cmd(t_lexer **headlex, t_simple_cmds **headcmd)
{
	t_lexer			*tmplex;
	t_simple_cmds	*tmpcmd;
	int				i;

	tmplex = *headlex;
	tmpcmd = *headcmd;
	if (!tmplex || !tmpcmd)
		return ;
	while (tmpcmd)
	{
		tmpcmd->str = ft_calloc(sizeof(char *), count_t_lexer(tmplex) + 3);
		if (!tmpcmd->str)
			return ;
		if (tmplex->token == PIPE && tmplex->next && tmplex->prev)
			tmplex = tmplex->next;
		i = 0;
		while (tmplex && tmplex->token != PIPE)
		{
			tmpcmd->str[i] = ft_strdup(tmplex->str);
			i++;
			tmplex = tmplex->next;
		}
		tmpcmd = tmpcmd->next;
	}
}

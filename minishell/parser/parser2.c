/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:15:45 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 16:11:26 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_lexer	*init_redir(t_lexer *curr)
{
	t_lexer	*redir;

	redir = ft_calloc(1, sizeof(t_lexer));
	if (!redir)
		return (NULL);
	redir->token = curr->token;
	redir->prev = NULL;
	redir->next = NULL;
	if (!curr->next)
	{
		redir->str = NULL;
		return (redir);
	}
	else
		redir->str = ft_strdup(curr->next->str);
	return (redir);
}

void	add_back_redir(t_simple_cmds *curr, t_lexer *new)
{
	t_lexer	*tmp;

	if (!curr->redirections)
	{
		new->prev = NULL;
		curr->redirections = new;
		return ;
	}
	tmp = curr->redirections;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	add_node_redir(t_simple_cmds *curr, t_lexer *redir)
{
	t_lexer	*tmp_redir;

	tmp_redir = NULL;
	if (!curr->redirections)
		curr->redirections = redir;
	else
	{
		if (!tmp_redir)
		{
			tmp_redir = curr->redirections;
			while (tmp_redir->next)
				tmp_redir = tmp_redir->next;
		}
		tmp_redir->next = redir;
		redir->prev = tmp_redir;
		tmp_redir = redir;
	}
}

void	add_redir(t_simple_cmds **head, t_lexer **lexer)
{
	t_simple_cmds	*tmpcmd;
	t_lexer			*tmplex;
	t_lexer			*redir;

	redir = NULL;
	tmpcmd = *head;
	tmplex = *lexer;
	if (!tmpcmd || !tmplex)
		return ;
	while (tmpcmd)
	{
		if (tmplex->token == PIPE && tmplex->next)
			tmplex = tmplex->next;
		while (tmplex && tmplex->token != PIPE)
		{
			if (tmplex->token == GREAT || tmplex->token == GREATGREAT
				|| tmplex->token == LESS || tmplex->token == LESSLESS)
				add_redir_splitted(tmpcmd, &tmplex, &redir, lexer);
			else
				tmplex = tmplex->next;
		}
		tmpcmd = tmpcmd->next;
	}
}

void	ft_free_cmd(t_simple_cmds **head)
{
	t_simple_cmds	*tmp;
	int				i;

	tmp = *head;
	while (tmp)
	{
		i = -1;
		while (tmp->str[++i])
			free(tmp->str[i]);
		tmp = tmp->next;
	}
}

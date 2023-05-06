/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:15:45 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/23 19:25:14 by chabrune         ###   ########.fr       */
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
	if (!curr->next)
		return (NULL);
	else
		redir->str = ft_strdup(curr->next->str);
	redir->next = NULL;
	return (redir);
}

void	add_back_redir(t_simple_cmds *curr, t_lexer *new)
{
	t_lexer	*tmp;

	if (!curr->redirections) // si *head est vide (si la chaine est vide)
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
// INVALID READ OF SIZE A GERER
void	add_redir(t_simple_cmds **head, t_lexer **lexer)
{
	t_simple_cmds	*tmpcmd;
	t_lexer			*tmplex;
	t_lexer			*redir;

	tmpcmd = *head;
	tmplex = *lexer;
	if (!tmpcmd || !tmplex)
		return ;
	while (tmpcmd)
	{
		if (tmplex->token == PIPE && tmplex->next)
			tmplex = tmplex->next;
		while (tmplex && tmplex->next && tmplex->token != PIPE)
		{
			if (tmplex->token == GREAT || tmplex->token == GREATGREAT
				|| tmplex->token == LESS || tmplex->token == LESSLESS)
			{
				tmpcmd->num_redirections++;
				redir = init_redir(tmplex);
				add_node_redir(tmpcmd, redir);
				if (tmplex->next)
					del_node(lexer, tmplex->next);
				del_node(lexer, tmplex);
				tmplex = *lexer;
			}
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
	t_lexer *tmplex;
	t_simple_cmds *tmpcmd;
	tmplex = *headlex;
	tmpcmd = *headcmd;
	int i;
	while (tmpcmd)
	{
		tmpcmd->str = ft_calloc(sizeof(char *), count_t_lexer(tmplex) + 3);
		if (tmplex->token == PIPE && tmplex->next && tmplex->prev)
		{
			tmplex = tmplex->next;
			tmpcmd->num_redirections += 1;
		}
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
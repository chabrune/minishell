/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:15:45 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/17 22:34:52 by chabrune         ###   ########.fr       */
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

	tmpcmd = *head;
	tmplex = *lexer;
	while (tmpcmd)
	{
		if (tmplex->token == PIPE && tmplex->next && tmplex->prev)
			tmplex = tmplex->next;
		while (tmplex && tmplex->next) //&& tmplex->token != PIPE)
		{
			if (tmplex->token == GREAT || tmplex->token == GREATGREAT
				|| tmplex->token == LESS || tmplex->token == LESSLESS)
			{
				redir = init_redir(tmplex);
				add_node_redir(tmpcmd, redir);
				del_node(lexer, tmplex->next);
				del_node(lexer, tmplex);
				tmplex = *lexer;
				// printf("redir str = %s\n", tmpcmd->redirections->next->str);
				// printf("redir token = %d\n", tmpcmd->redirections->token);
			}
			else
				tmplex = tmplex->next;
		}
		tmpcmd = tmpcmd->next;
	}
	print_t_lexer_list(*head);
}

void	ft_free_cmd(t_simple_cmds **head)
{
	t_simple_cmds *tmp;
	int i;

	tmp = *head;
	while (tmp)
	{
		i = -1;
		while(tmp->str[++i])
			free(tmp->str[i]);
		tmp = tmp->next;
	}
}

void	last_lexer_to_strs_cmd(t_lexer **headlex, t_simple_cmds **headcmd)
{
	t_lexer *tmplex;
	t_simple_cmds *tmpcmd;
	tmplex = *headlex;
	tmpcmd = *headcmd;
	int i;
	// int j;
	// print_cmd(headcmd);
	// print_t_lexer_list(*headcmd);
	// ft_free_cmd(&tmpcmd);
	while (tmpcmd)
	{
		i = 0;
		// free_all_tab(tmpcmd->str);
		// int count = 0;
		// while (tmplex)
		// 	count++;
		// tmp->str = ft_calloc(sizeof(char *), );
		if (tmplex->token == PIPE && tmplex->next && tmplex->prev)
			tmplex = tmplex->next;
		while (tmplex && tmplex->next && tmplex->token != PIPE)
		{
			// printf("lexer = %s\n", tmplex->str);
			tmpcmd->str[i] = ft_strdup(tmplex->str);
			i++;
			// printf("rest of lexer : %s\n", tmpcmd->str[i]);
			tmplex = tmplex->next;
		}
		// j = -1;
		// while(tmpcmd->str[++j])
		// 	printf("cmd = %s\n", tmpcmd->str[j]);
		tmpcmd = tmpcmd->next;
	}
}
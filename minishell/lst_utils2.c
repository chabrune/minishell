/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:58:25 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/12 23:19:15 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstclear_cmds(t_simple_cmds **lst, void (*del)(void *))
{
	t_simple_cmds	*current;
	t_simple_cmds	*temp;

	if (lst && *lst)
	{
		current = *lst;
		while (current)
		{
			temp = current->next;
			lstdelone_cmds(current, del);
			current = temp;
		}
	}
}

void	lstclear_all(t_lexer **lexer, t_simple_cmds **cmds, t_tools *tools)
{
	if (lexer && *lexer)
		lstclear_lexer(lexer, free);
	if (cmds && *cmds)
		lstclear_cmds(cmds, free);
	if (tools)
		lstclear_tools(tools);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:58:25 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 16:51:41 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstclear_cmds(t_simple_cmds **lst, void (*del)(void *))
{
	t_simple_cmds *temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			lstdelone_cmds(*lst, del);
			(*lst) = temp;
		}
	}
}

void	lstclear_all(t_lexer **lexer, t_simple_cmds **cmds, t_tools *tools)
{
	lstclear_lexer(lexer, free);
	lstclear_cmds(cmds, free);
	lstclear_tools(tools);
}

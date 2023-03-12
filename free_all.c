/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:49:38 by emuller           #+#    #+#             */
/*   Updated: 2023/03/12 12:54:03 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstdelone_tools(void *lst)
{
	if (lst == NULL)
		return ;
	free(lst->str);
	lst = NULL;
	free(lst);
}

void	lstclear_lexer(void **lst, void (*del)(void *))
{
	void	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			lstdelone_lexer(*lst);
			(*lst) = temp;
		}
	}
}

void    free_all(t_lexer *lexer, t_tools *tools, t_simple_cmds *cmds)
{
    
}
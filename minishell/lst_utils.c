/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:42:20 by emuller           #+#    #+#             */
/*   Updated: 2023/05/12 23:25:39 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstdelone_lexer(t_lexer *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del)
		free(lst->str);
	free(lst->buffer);
	lst->next = NULL;
	free(lst);
	lst = NULL;
}

void	lstclear_lexer(t_lexer **lst, void (*del)(void *))
{
	t_lexer	*current;
	t_lexer	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		lstdelone_lexer(current, del);
		current = next;
	}
	*lst = NULL;
}

void	lstdelone_cmds(t_simple_cmds *lst, void (*del)(void *))
{
	int		i;
	t_lexer	*tmp;
	t_lexer	*next;

	i = -1;
	if (lst->str)
		while (lst->str[++i])
			free(lst->str[i]);
	free(lst->str);
	if (lst->hd_file_name)
		free(lst->hd_file_name);
	if (lst->redirections)
	{
		tmp = lst->redirections;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->str)
				free(tmp->str);
			free(tmp);
			tmp = next;
		}
	}
	del(lst);
}

void	lstclear_tools(t_tools *tools)
{
	int	i;

	if (!tools)
		return ;
	i = -1;
	if (tools->pid)
		free(tools->pid);
	reset_tool(&tools);
}

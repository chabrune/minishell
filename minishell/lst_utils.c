/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:42:20 by emuller           #+#    #+#             */
/*   Updated: 2023/05/06 16:24:22 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstdelone_lexer(t_lexer *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del)
		del(lst->str);
	free(lst);
	lst = NULL;
}

void	lstclear_lexer(t_lexer **lst, void (*del)(void *))
{
	t_lexer	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			lstdelone_lexer(*lst, del);
			(*lst) = temp;
		}
	}
}

void	lstdelone_cmds(t_simple_cmds *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	int i;
	t_lexer *tmp;
	t_lexer *next;

	i = -1;
	if(lst->str)
		while(lst->str[++i])
			free(lst->str[i]);
	free(lst->str);
	if(lst->hd_file_name)
		free(lst->hd_file_name);
	if(lst->redirections)
	{
		tmp = lst->redirections;
		while(tmp)
		{
			next = lst->redirections->next;
			if(tmp->str)
				free(tmp->str);
			free(tmp);
			tmp = next;
		}
	}
	del(lst);
}

void	lstclear_tools(t_tools *tools)
{
	if(!tools)
		return ;
	int i;

	i = -1;
	if(tools->cmd)
		free(tools->cmd);
	if(tools->input)
		free(tools->input);
	i = -1;
	if(tools->inputs)
	{
		while(tools->inputs[++i])
			free(tools->inputs[i]);
	}
	if(tools->inputs)
		free(tools->inputs);
	if(tools->path)
		free(tools->path);
	i = -1;
	if(tools->paths)
	{
		while(tools->paths[++i])
			free(tools->paths[i]);
		free(tools->paths);
	}
	if(tools->pid)
		free(tools->pid);
	reset_tool(&tools);
}

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
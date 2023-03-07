/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:39:12 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/07 15:38:19 by chabrune         ###   ########.fr       */
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
	if(del)
		del(lst->str);
	del(lst);
}

void	lstclear_cmds(t_simple_cmds **lst, void (*del)(void *))
{
	t_simple_cmds	*temp;

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

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds)
{
	(void)scmds;
	(void)lexer;
	while(42)
	{
		tool->input = readline("EmmaLaBest> ");
		// if(check_closed_quotes(tool->input))
		// 	continue;
		// tool->inputs = ft_split(tool->input, ' ');
		lexer = ft_lexer(tool->input);
		scmds = group_command(&lexer);
		print_tokens(lexer);
		add_history(tool->input);
		if(lexer)
			lstclear_lexer(&lexer, free);
		if(scmds)
			lstclear_cmds(&scmds, free);
		free(tool->input);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	if(argc == 1)
	{
		t_tools tool;
		t_lexer	lexer;
		t_simple_cmds scmds;
		minishell_loop(&tool, &lexer, &scmds);
	}
	else
		return(1);
	return(0);
		
}
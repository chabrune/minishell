/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:39:12 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/01 08:50:11 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds)
{
	while(42)
	{
		tool->input = readline("EmmaLaBest> ");
		tool->inputs = ft_split(tool->input, ' ');
		lexer = ft_lexer(tool->input);
		scmds = group_command(lexer);
		print_cmds(scmds);
		// print_tokens(lexer);
		add_history(tool->input);
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
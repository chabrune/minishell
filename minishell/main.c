/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:39:12 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/13 18:47:43 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds)
{
	while(42)
	{
		tool->input = readline("EmmaLaBest> ");
		// if(check_closed_quotes(tool->input))
		// 	continue;
		// tool->inputs = ft_split(tool->input, ' ');
		lexer = ft_lexer(tool->input);
		scmds = group_command(&lexer);
		//choose_bultins(tool, scmds);
		find_redir(&scmds, &lexer);
		print_t_lexer_list(scmds);
		add_history(tool->input);
		lstclear_lexer(&lexer, free);
		print_tokens(lexer);
		lstclear_cmds(&scmds, free);
		free(tool->input);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_tools tool;
	t_lexer	lexer;
	t_simple_cmds scmds;

	if (argc == 1 || argv[1])
	{
		tool.envp = dup_env(envp); // il faudra penser a free
		minishell_loop(&tool, &lexer, &scmds);
	}
	else
		return(1);
	return(0);
}
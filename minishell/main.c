/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:39:12 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/06 14:12:05 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds)
{
	int i;

	while(42)
	{
		tool->input = readline("EmmaLaBest> ");
		// if(check_closed_quotes(tool->input))
		// 	continue;
		tool->inputs = ft_split(tool->input, ' ');
		lexer = ft_lexer(tool->input, tool);
		print_tokens(lexer);
		scmds = group_command(&lexer);
		// choose_bultins(tool, scmds);
		find_redir(&scmds, &lexer);
		print_t_lexer_list(scmds);
		fill_cmd_heredoc(&scmds, tool->input);
		i = count_cmd(&scmds);
		if(i == 1)
			one_command(&scmds, tool);
		else
			multiple_commands(&scmds, tool);
		add_history(tool->input);
		lstclear_lexer(&lexer, free);
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
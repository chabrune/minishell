/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:34:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/12 11:51:18 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds)
{
	// int i;
	int i;

	while(42)
	{
		tool->input = readline("CharlesLeBebou> ");
		tool->inputs = ft_split(tool->input, ' ');
		lexer = ft_lexer(tool->input, tool);
		scmds = group_command(&lexer);
		// find_redir(&scmds, &lexer); // <-- C CE TRUC DE MERDE QUI NOUS A BLOQUE
		fill_cmd_heredoc(&scmds, tool->input);
		// print_tokens(lexer);
		// print_t_lexer_list(scmds);
		// print_cmd(&scmds);
		// IL FAUDRAIT METTRE LA FONCTION CHOOSE BUILTINS DANS ONE CMD ET MULTIPLE CMDS, MAIS JE COMPREND PAS COMMENT ELLES FONCTIONNENT DONC JE SAIS PAS OU
		// if (is_builtins(scmds) == 1)
		// 	choose_bultins(tool, scmds);
		// else
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
<<<<<<< HEAD
}
=======
}
>>>>>>> 5e2d3013784535b3a6a72db3163cbaf24b5dc488

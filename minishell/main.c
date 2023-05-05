/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:34:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/02 20:30:33 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds)
{
	int i;

	while(42)
	{
		tool->input = readline("MiniPROUT> ");
		if (!tool->input)
		{
			printf("exit\n");
			exit(0);
		}
		tool->inputs = ft_split(tool->input, ' ');
		lexer = ft_lexer(tool->input, tool);
		scmds = group_command(&lexer);
		add_redir(&scmds, &lexer);
		last_lexer_to_strs_cmd(&lexer, &scmds);
		// print_cmd(&scmds);
		// print_tokens(lexer);
		// print_t_lexer_list(scmds);
		i = count_cmd(&scmds);
		// in_cmd = 1;
		if(i == 1)
			one_command(scmds, tool);
		else
			multiple_commands(&scmds, tool);
		// in_cmd = 0;
		if (tool->input[0] != '\0')
			add_history(tool->input);
		lstclear_lexer(&lexer, free);
		lstclear_cmds(&scmds, free);
		free(tool->input);
		free(tool->inputs);
	}
}
int main(int argc, char **argv, char **envp)
{
	t_tools tool;
	t_lexer	lexer;
	t_simple_cmds scmds;
	
	if (argc == 1 || argv[1])
	{
		// handle_signal();
		tool.envp = dup_env(envp); // il faudra penser a free
		// in_cmd = 0;
		// stop_heredoc = 0;
		minishell_loop(&tool, &lexer, &scmds);
	}
	else
		return(1);
	return(0);
}
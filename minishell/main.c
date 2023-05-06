/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:34:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/06 15:10:03 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds, char **env)
{
	int	i;

	while (42)
	{
		init_tool(&tool, env);
		tool->input = readline("MiniPROUT> ");
		if (!tool->input)
		{
			printf("exit\n");
			my_exit(tool, scmds, lexer);
		}
		tool->inputs = ft_split(tool->input, ' ');
		lexer = ft_lexer(tool->input, tool);
		scmds = group_command(&lexer);
		add_redir(&scmds, &lexer);
		last_lexer_to_strs_cmd(&lexer, &scmds);
		i = count_cmd(&scmds);
		in_cmd = 1;
		if (i == 1)
			one_command(scmds, tool, lexer);
		else
			multiple_commands(&scmds, tool, lexer);
		in_cmd = 0;
		if (tool->input[0] != '\0')
			add_history(tool->input);
		lstclear_lexer(&lexer, free);
		lstclear_cmds(&scmds, free);
		lstclear_tools(tool);
	}
}

int	init_tool(t_tools **tools, char **env)
{
	*tools = ft_calloc(sizeof(t_tools), 1);
	if (!(*tools))
		return (EXIT_FAILURE);
	(*tools)->cmd = NULL;
	(*tools)->envp = dup_env(env);
	(*tools)->input = NULL;
	(*tools)->inputs = NULL;
	(*tools)->path = NULL;
	(*tools)->paths = NULL;
	(*tools)->pid = NULL;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools 		*tool;
	t_lexer 		*lexer;
	t_simple_cmds 	*scmds;

	tool = NULL;
	lexer = NULL;
	scmds = NULL;
	if (argc == 1 || argv[1])
	{
		handle_signal();
		in_cmd = 0;
		stop_heredoc = 0;
		minishell_loop(tool, lexer, scmds, envp);
	}
	else
		return (1);
	return (0);
}
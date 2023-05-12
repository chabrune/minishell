/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:34:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/12 19:35:50 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds,
		char **env)
{
	int	i;

	init_tool(&tool, env);
	while (42)
	{
		g_global.in_child = 1;
		g_global.stop_heredoc = 0;
		tool->input = readline("MiniPROUT> ");
		if (!tool->input)
		{
			printf("exit\n");
			my_exit(tool, scmds, lexer);
		}
		if (tool->input[0] != '\0')
			add_history(tool->input);
		lexer = ft_lexer(tool->input, tool);
		if (check_pipe(lexer) == 1)
		{
			lstclear_all(&lexer, &scmds, tool);
			continue ;
		}
		if (!lexer)
		{
			lstclear_all(&lexer, &scmds, tool);
			continue ;
		}
		scmds = group_command(&lexer);
		add_redir(&scmds, &lexer);
		last_lexer_to_strs_cmd(&lexer, &scmds);
		if (scmds->redirections)
		{
			if (!scmds->redirections->str)
			{
				printf("FDP\n");
				lstclear_all(&lexer, &scmds, tool);
				ft_putendl_fd("minishell: syntax error", 2);
				g_global.error_num = 258;
				continue ;
			}
		}
		i = count_cmd(&scmds);
		g_global.in_cmd = 1;
		if (i == 1)
			one_command(scmds, tool, lexer);
		else
			multiple_commands(&scmds, tool);
		g_global.in_cmd = 0;
		lstclear_all(&lexer, &scmds, tool);
		g_global.error_num = 0;
	}
}

void	reset_tool(t_tools **tools)
{
	(*tools)->cmd = NULL;
	(*tools)->input = NULL;
	(*tools)->inputs = NULL;
	(*tools)->path = NULL;
	(*tools)->paths = NULL;
	(*tools)->pid = NULL;
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

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	t_tools			*tool;
	t_lexer			*lexer;
	t_simple_cmds	*scmds;

	tool = NULL;
	lexer = NULL;
	scmds = NULL;
	g_global.error_num = 0;
	if (argc == 1 || argv[1])
	{
		handle_signal();
		g_global.in_cmd = 0;
		g_global.stop_heredoc = 0;
		g_global.in_heredoc = 0;
		g_global.error_num = 0;
		minishell_loop(tool, lexer, scmds, envp);
		free(tool);
	}
	else
		return (1);
	return (0);
}

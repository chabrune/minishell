/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:34:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/14 16:39:09 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_tools *tool, t_lexer **lexer, t_simple_cmds **scmds)
{
	if (!tool->input_copy)
	{
		printf("exit\n");
		my_exit(tool, *scmds, *lexer);
	}
	if (tool->input_copy[0] != '\0')
		add_history(tool->input_copy);
	*lexer = ft_lexer(tool);
	if (!*lexer || check_pipe(*lexer) == 1)
	{
		lstclear_lexer(lexer, free);
		return (1);
	}
	free(tool->input_copy);
	*scmds = group_command(lexer);
	add_redir(scmds, lexer);
	last_lexer_to_strs_cmd(lexer, scmds);
	if ((*scmds)->redirections && !(*scmds)->redirections->str)
	{
		lstclear_all(lexer, scmds, tool);
		ft_putendl_fd("minishell: syntax error", 2);
		g_global.error_num = 258;
		return (2);
	}
	return (0);
}

void	handle_commands(t_simple_cmds *scmds, t_tools *tool, t_lexer *lexer)
{
	int	i;

	i = count_cmd(&scmds);
	g_global.in_cmd = 1;
	if (i == 1)
		one_command(scmds, tool, lexer);
	else
		multiple_commands(&scmds, tool);
	g_global.in_cmd = 0;
	lstclear_all(&lexer, &scmds, tool);
}

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds,
			char **env)
{
	init_tool(&tool, env);
	while (42)
	{
		tool->input = readline("MiniPROUT> ");
		if (!tool->input)
		{
			printf("exit\n");
			my_exit(tool, scmds, lexer);
		}
		if (tool->input[0] != '\0')
			add_history(tool->input);
		tool->input_copy = ft_strdup(tool->input);
		free(tool->input);
		if (handle_input(tool, &lexer, &scmds) > 0)
		{
			free(tool->input_copy);
			continue ;
		}
		handle_commands(scmds, tool, lexer);
		free(tool->input_copy);
	}
}

void	reset_tool(t_tools **tools)
{
	(*tools)->cmd = NULL;
	if ((*tools)->input_copy)
		free((*tools)->input_copy);
	(*tools)->input = NULL;
	(*tools)->inputs = NULL;
	(*tools)->path = NULL;
	(*tools)->paths = NULL;
	(*tools)->pid = NULL;
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
		g_global.error_num = 0;
		minishell_loop(tool, lexer, scmds, envp);
		free(tool->input_copy);
		free(tool);
	}
	else
		return (1);
	return (0);
}

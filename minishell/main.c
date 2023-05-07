/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:34:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/07 18:35:19 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_t_lexer_list(t_simple_cmds *head)
{
	t_lexer			*current;
	t_simple_cmds	*tmp;

	if (!head)
		return ;
	current = head->redirections;
	tmp = head;
	while (tmp)
	{
		while (current)
		{
			printf("Token: %d, Filename: %s\n", current->token, current->str);
			current = current->next;
		}
		tmp = tmp->next;
	}
}

void	print_tokens(t_lexer *head)
{
	t_lexer	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("=================\n");
		printf("Token: %s\n", tmp->str);
		printf("Token type: %d\n", tmp->token);
		printf("Index: %d\n", tmp->i);
		printf("=================\n");
		tmp = tmp->next;
	}
}

void	minishell_loop(t_tools *tool, t_lexer *lexer, t_simple_cmds *scmds,
		char **env)
{
	int	i;

	init_tool(&tool, env);
	while (42)
	{
		error_num = 0;
		stop_heredoc = 0;
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
		// print_cmd(&scmds);
		// print_tokens(lexer);
		// print_t_lexer_list(scmds);
		i = count_cmd(&scmds);
		in_cmd = 1;
		if (i == 1)
			one_command(scmds, tool, lexer);
		else
			multiple_commands(&scmds, tool);
		in_cmd = 0;
		if (tool->input[0] != '\0')
			add_history(tool->input);
		lstclear_lexer(&lexer, free);
		lstclear_cmds(&scmds, free);
		lstclear_tools(tool);
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

int	main(int argc, char **argv, char **envp)
{
	t_tools *tool;
	t_lexer *lexer;
	t_simple_cmds *scmds;

	tool = NULL;
	lexer = NULL;
	scmds = NULL;
	error_num = 0;
	if (argc == 1 || argv[1])
	{
		handle_signal();
		in_cmd = 0;
		stop_heredoc = 0;
		in_heredoc = 0;
		minishell_loop(tool, lexer, scmds, envp);
		free(tool);
	}
	else
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:39:12 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/03 11:02:00 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_shell *shell, t_lexer *lexer, t_simple_cmds *scmds)
{
	(void)scmds;
	while(42)
	{
		shell->input = readline("EmmaLaBest> ");
		shell->inputs = ft_split(shell->input, ' ');
		lexer = ft_lexer(shell->input);
		ft_parser(lexer);
		print_tokens(lexer);
		add_history(shell->input);
		free(shell->input);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	if(argc == 1)
	{
		t_shell shell;
		t_lexer	lexer;
		t_simple_cmds scmds;
		minishell_loop(&shell, &lexer, &scmds);
	}
	else
		return(1);
	return(0);
		
}
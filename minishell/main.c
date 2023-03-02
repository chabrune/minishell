/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:39:12 by chabrune          #+#    #+#             */
/*   Updated: 2023/02/28 23:05:15 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_shell *shell, t_lexer *lexer)
{
	(void)lexer;
	while(42)
	{
		shell->input = readline("EmmaLaBest> ");
		shell->inputs = ft_split(shell->input, ' ');
		lexer = ft_lexer(shell->input);
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
		minishell_loop(&shell, &lexer);
	}
	else
		return(1);
	return(0);
		
}
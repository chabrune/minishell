/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:38:43 by emuller           #+#    #+#             */
/*   Updated: 2023/05/08 19:15:25 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int sig)
{
	(void)sig;
	g_global.stop_heredoc = 1;
	g_global.error_num = 1;
	if (g_global.in_heredoc == 0)
	{
		printf("\n");
		rl_redisplay();
	}
	if (g_global.in_cmd)
	{
		if (g_global.in_heredoc == 1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			exit(0);
		}
		rl_replace_line("", 0);
		rl_on_new_line();
		g_global.error_num = 130;
		return ;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signal(void)
{
	if (g_global.in_child == 0)
	{
		signal(SIGINT, control_c);
		signal(SIGQUIT, SIG_IGN);
		rl_catch_signals = 0;
	}
}

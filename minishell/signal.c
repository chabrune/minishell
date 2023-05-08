/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:38:43 by emuller           #+#    #+#             */
/*   Updated: 2023/05/08 16:50:12 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int sig)
{
	(void)sig;
	stop_heredoc = 1;
	error_num = 1;
	if (in_heredoc == 0)
	{
		printf("\n");
		rl_redisplay();
	}
	if (in_cmd)
	{
		if (in_heredoc == 1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			exit(0);
		}
		rl_replace_line("", 0);
		rl_on_new_line();
		error_num = 130;
		return ;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signal(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:38:43 by emuller           #+#    #+#             */
/*   Updated: 2023/05/13 18:28:14 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int sig)
{
	(void)sig;
	g_global.error_num = 1;
	if (g_global.in_cmd == 1)
		printf("\n");
	if (g_global.in_cmd == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}

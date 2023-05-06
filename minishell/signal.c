/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:38:43 by emuller           #+#    #+#             */
/*   Updated: 2023/05/06 11:34:45 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int sig)
{
	(void)sig;
	printf("\n");
	if (in_cmd) // check si on est dans une commande
	{
		stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	rl_replace_line("", 0);
	rl_redisplay();
	rl_on_new_line();
}

void	handle_signal(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}
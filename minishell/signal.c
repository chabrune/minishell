/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:38:43 by emuller           #+#    #+#             */
/*   Updated: 2023/04/24 15:38:37 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    control_c()
{
    printf("\n");
    if (in_cmd) // check si on est dans une commande
    {
        // stop_heredoc = 1;
        rl_replace_line("", 0);
        rl_redisplay();
        return ;
    }
    rl_replace_line("", 0);
    rl_redisplay();
    rl_on_new_line();   
}

void    handle_signal()
{
    signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
    rl_catch_signals = 0;
}
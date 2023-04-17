/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:38:43 by emuller           #+#    #+#             */
/*   Updated: 2023/04/17 16:06:08 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    control_c()
{
    if () // check si on est dans une commande
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    
}

void    handle_signal()
{
    signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
    rl_catch_signals = 0;
}
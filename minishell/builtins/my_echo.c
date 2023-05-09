/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:50:24 by emuller           #+#    #+#             */
/*   Updated: 2023/05/09 17:34:58 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_echo(t_simple_cmds *cmd)
{
	int		i;
	bool	n;

	i = 1;
	n = 0;
	while (cmd->str[1] && cmd->str[1][0] == '-' && cmd->str[1][i] == 'n')
	{
		i++;
		if (cmd->str[1][i] == 0)
			n = 1;
	}
	if (i > 1)
		i = 2;
	while (cmd->str[i])
	{
		ft_putstr_fd(cmd->str[i], STDOUT_FILENO);
		i++;
		if (cmd->str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

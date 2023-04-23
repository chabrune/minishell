/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:50:24 by emuller           #+#    #+#             */
/*   Updated: 2023/04/23 18:50:13 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_echo(t_simple_cmds *cmd)
{
	int i;
	bool n;

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
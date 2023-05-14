/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:50:24 by emuller           #+#    #+#             */
/*   Updated: 2023/05/14 14:45:14 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_echo(t_simple_cmds *cmd)
{
	int		i;
	int		j;
	bool	n;

	j = 1;
	i = 1;
	n = 0;
	while (cmd->str[j] && cmd->str[j][0] == '-' && cmd->str[j][1] == 'n')
	{
		i = 1;
		while (cmd->str[j][i] == 'n')
			i++;
		if (cmd->str[j][i] == 0)
			n++;
		else
			break ;
		j++;
	}
	print_echo(cmd, j);
	if (n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_echo(t_simple_cmds *cmd, int j)
{
	while (cmd->str[j])
	{
		ft_putstr_fd(cmd->str[j], STDOUT_FILENO);
		j++;
		if (cmd->str[j])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

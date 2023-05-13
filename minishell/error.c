/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:12:07 by emuller           #+#    #+#             */
/*   Updated: 2023/05/13 14:38:29 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char *str, t_tools *tools)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_global.error_num = 127;
	if (tools)
		lstclear_tools(tools);
	free(tools->cmd);
	free(tools->paths);
	exit(127);
}

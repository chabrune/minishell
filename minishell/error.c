/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:12:07 by emuller           #+#    #+#             */
/*   Updated: 2023/05/13 17:13:10 by chabrune         ###   ########.fr       */
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
	free(tools->input);
	exit(127);
}

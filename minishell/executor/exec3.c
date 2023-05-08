/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:03:34 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 13:04:20 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_child(t_tools *tools)
{
	int i;

	i = -1;
	while (tools->paths[++i])
		free(tools->paths[i]);
	free(tools->paths);
	free(tools->cmd);
}
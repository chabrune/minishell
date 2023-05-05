/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:03:34 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/06 00:12:59 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_child(t_tools **tools)
{
	int	i;

	i = -1;
	while ((*tools)->paths[++i])
		free((*tools)->paths[i]);
	free((*tools)->paths);
	free((*tools)->cmd);
}

void	fill_tools_param(t_simple_cmds *curr, t_tools *tools)
{
	tools->path = find_path(tools->envp);
	tools->paths = ft_split(tools->path, ':');
	tools->cmd = get_cmd(curr, tools);
}

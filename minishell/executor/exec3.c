/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:03:34 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/09 16:37:25 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_cmd_and_paths(t_tools *tools)
{
	int	i;

	i = -1;
	free(tools->cmd);
	while (tools->paths[++i])
		free(tools->paths[i]);
	free(tools->paths);
}

void	fill_tools_param(t_simple_cmds *curr, t_tools *tools)
{
	tools->path = find_path(tools->envp);
	tools->paths = ft_split(tools->path, ':');
	tools->cmd = get_cmd(curr, tools);
}

void	one_command_split(t_simple_cmds *curr, t_tools *tools)
{
	fill_tools_param(curr, tools);
	fill_cmd_heredoc(curr, tools);
	dup_heredoc(curr);
}

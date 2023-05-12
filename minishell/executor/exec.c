/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:40:37 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/12 19:29:24 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	wait_process(t_tools *tools, t_simple_cmds **head)
{
	int	i;
	int	status;

	i = -1;
	while (++i < count_cmd(head))
	{
		if (kill(tools->pid[i], 0) == 0)
			waitpid(tools->pid[i], &status, 0);
		waitpid(tools->pid[i], &status, 0);
	}
	return (EXIT_SUCCESS);
}

int	multiple_commands(t_simple_cmds **head, t_tools *tools)
{
	t_simple_cmds	*tmp;
	int				j;
	int				pipes[2];
	int				fd_in;

	ft_memset(pipes, 0, sizeof(pipes));
	j = count_cmd(head);
	tools->pid = ft_calloc(sizeof(int), j + 1);
	tmp = *head;
	fd_in = STDIN_FILENO;
	while (tmp)
	{
		fill_all(tmp, tools);
		if (tmp->next)
			pipe(pipes);
		ft_fork(tools, tmp, pipes, fd_in);
		close(pipes[1]);
		if (tmp->prev)
			close(fd_in);
		fd_in = ft_check_heredoc(tools, tmp, pipes);
		tmp = tmp->next;
		free_cmd_and_paths(tools);
	}
	wait_process(tools, head);
	return (0);
}

int	handle_cmd(t_simple_cmds *curr, t_tools *tools)
{
	if (!tools->cmd || !curr->str)
	{
		free_cmd_and_paths(tools);
		g_global.error_num = cmd_not_found(curr->str[0]);
		my_exit(tools, curr, NULL);
	}
	if (tools->cmd && curr->str)
	{
		execve(tools->cmd, curr->str, tools->envp);
		g_global.error_num = cmd_not_found(curr->str[0]);
		free_cmd_and_paths(tools);
		my_exit(tools, curr, NULL);
	}
	return (0);
}

char	*find_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

char	*get_cmd(t_simple_cmds *cmd, t_tools *tools)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	if (!cmd->str)
		return (NULL);
	if (!access(cmd->str[0], F_OK))
		return (ft_strdup(cmd->str[0]));
	while (tools->paths[i])
	{
		tmp = ft_strjoin(tools->paths[i], "/");
		command = ft_strjoin(tmp, cmd->str[0]);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

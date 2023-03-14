/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:40:37 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/14 18:21:07 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	one_command(t_simple_cmds **head, t_tools *tools)
{
	t_simple_cmds *curr;
	int pid;
	int fdfile;
	curr = *head;
//if cmd == cd / exit / export / unset --> Exec without child
	tools->path = find_path(tools->envp);
	tools->paths = ft_split(tools->path, ':');
	tools->cmd = get_cmd(tools->paths, curr->str[0]);
	if(curr->redirections && curr->redirections->token == LESS)
	{
		fdfile = open(curr->redirections->str, O_RDONLY);
		if(fdfile == -1)
		{
			perror("Open : ");
			return(EXIT_FAILURE);
		}
		if(dup2(fdfile, STDIN_FILENO) == -1)
		{
			perror("Dup2 : ");
			return(EXIT_FAILURE);
		}
	}
	pid = fork();
	if(pid == -1)
	{
		perror("Fork : ");
		return(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		execve(tools->cmd, &curr->str[1], tools->envp);
		perror("Exceve : ");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	return(0);
}

char	*find_path(char **env)
{
	while (strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

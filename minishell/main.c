/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:39:12 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/02 15:54:03 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void    read_line(char *input, t_shell *shell)
// {
// 	int i;

// 	i = -1;
// 	while(shell->prompt[++i])
// 	{
// 		if(!strncmp(shell->prompt[i], "echo", 5))
// 			ft_echo();
// 		else if(!strncmp(shell->prompt[i], "cd", 3))
// 			ft_cd();
// 		else if(!strncmp(shell->prompt[i], "pwd", 4))
// 			ft_pwd();
// 		else if(!strncmp(shell->prompt[i], "export", 7))
// 			ft_export();
// 		else if(!strncmp(shell->prompt[i], "unset", 6))
// 			ft_unset();
// 		else if(!strncmp(shell->prompt[i], "env", 4))
// 			ft_env();
// 		else if(!strncmp(shell->prompt[i], "exit", 5))
// 			ft_exit();
// 	}
// }

int	error_msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

int	error_and_exit(char *error)
{
	perror(error);
	exit(1);
}

// int	child1_process(t_shell *shell)
// {
// 	shell->cmd = get_cmd(shell->env_paths, shell->inputs[0]);
// 	execve(shell->cmd, NULL, shell->env_paths);
// 	perror("exceve");
// 	exit(EXIT_FAILURE);
// 	return (0);
// }

int	quote_unclosed(char *input)
{
	int i;

	i = 0;
	while(*input)
	{
		if(*input == 34 || *input == 39)
			i++;
	}
	if(i % 2 != 0)
		return(1);
	return(0);
}

void	shell_loop(t_shell *shell)
{
	while(42)
	{
		shell->input = readline("EmmaLaBest$> ");
		shell->inputs = ft_split(shell->input, ' ');
		if(!quote_unclosed(shell->input))
			ft_lexer(shell->input);
		add_history(shell->input);
		free(shell->input);
	}
}

// char	*get_cmd(char **paths, char *cmd)
// {
// 	char	*tmp;
// 	char	*command;

// 	while (paths)
// 	{
// 		tmp = ft_strjoin(*paths, "/");
// 		command = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(command, 0) == 0)
// 			return (command);
// 		free(command);
// 		paths++;
// 	}
// 	return (NULL);
// }

char *get_env_path(char **env)
{
	while (strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	ft_init_shell(t_shell *shell, char **ar, char **env)
{
	(void)ar;
	shell->env_path = get_env_path(env);
	shell->env_paths = ft_split(shell->env_path, ':');
}

int main(int argc, char **argv, char **envp)
{
	if(argc == 1)
	{
		t_shell	shell;
		ft_init_shell(&shell, argv, envp);
		shell_loop(&shell);
	}
	else
		return(error_msg("ERREUR INPUT\n"));
}
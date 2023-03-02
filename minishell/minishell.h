/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:38:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/02 12:52:29 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>

typedef struct s_shell
{
	char *input;
	char **inputs;
	char *env_path;
	char **env_paths;
}   t_shell;

int		error_msg(char *error);
int		error_and_exit(char *error);
void	shell_loop(t_shell *shell);
char	*get_cmd(char **paths, char **cmd);
char 	*get_env_path(char **env);
void	ft_init_shell(t_shell *shell, char **ar, char **env);


#endif
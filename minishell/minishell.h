/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:38:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/02 15:54:01 by chabrune         ###   ########.fr       */
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

typedef enum e_tokens
{
    WORD,
    PIPE,
    LESS_THAN,
    DOUBLE_LESS_THAN,
    GREATER_THAN,
    DOUBLE_GREATER_THAN
} t_tokens;

typedef struct s_lexer
{
	char    	*str;
	t_tokens        token;
	int		i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_shell
{
	char *input;
	char **inputs;
	char *env_path;
	char **env_paths;
	char *cmd;
}   t_shell;

t_lexer	ft_lexer(char *line);
int		error_msg(char *error);
int		error_and_exit(char *error);
void	shell_loop(t_shell *shell);
char	*get_cmd(char **paths, char *cmd);
char 	*get_env_path(char **env);
void	ft_init_shell(t_shell *shell, char **ar, char **env);


#endif
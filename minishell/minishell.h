/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:38:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/02/28 23:01:36 by chabrune         ###   ########.fr       */
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
# include <string.h>
# include <ctype.h>

typedef enum s_tokens
{
    WORD = 1,
    PIPE,
    LESS,
    LESSLESS,
    GREAT,
    GREATGREAT
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_shell
{
    char *input;
    char **inputs;
}              t_shell;

t_lexer *new_token(char *str, t_tokens token, int i);
t_lexer *ft_lexer(char *input);
void print_tokens(t_lexer *head);

#endif
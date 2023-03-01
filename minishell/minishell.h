/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:38:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/01 08:40:16 by chabrune         ###   ########.fr       */
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
# include <stdbool.h>

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

typedef struct s_tools
{
    char    *args;
    char    **paths;
    char    **envp;
    t_lexer *lexer_list;
    int     pipes;
    int     *pid;
    char    *input;
    char    **inputs;
}   t_tools;

typedef struct s_simple_cmds
{
	char                    **str;
	int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

t_lexer         *new_token(char *str, t_tokens token, int i);
t_lexer         *ft_lexer(char *input);
void			print_tokens(t_lexer *head);
t_simple_cmds	*group_command(t_lexer *lexer);
t_simple_cmds	*ft_parse(t_lexer *lexer);
void            print_cmds(t_simple_cmds *cmds);
void            print_commands(t_simple_cmds *cmds);
int             is_redirection(int token);
int             is_builtin(char *cmd);
t_lexer         *lexer_remove_node(t_lexer *lexer);
t_lexer         *lexer_add_node(t_lexer *lexer, int token, char *str);




#endif
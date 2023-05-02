/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:38:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/02 13:15:00 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

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
    char    *args; // tu veux mettre quoi la dedans?
    char    **paths; // tu veux mettre quoi la dedans?
    char    *path; //Mdr j'en rajoute tqt
    char    *cmd;
    char    **envp;
    t_lexer *lexer_list; // je suis pas sure qu'on en a besoin ici
    int     *pipes;
    int     *pid;
    int     fd[2];
    int     hd_fd;
    char    *input;
    char    **inputs;
}   t_tools;

typedef struct s_simple_cmds
{
    int                     fd;
	char                    **str;
	int                     num_redirections;
	char                    *hd_file_name; 
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

# include "builtins/builtins.h"
# include "parser/parser.h"
# include "executor/exec.h"
# include "expander/expander.h"
# include "lexer/lexer.h"

// int in_cmd;
// int stop_heredoc;

t_lexer         *new_token(char *str, t_tokens token, int i);
t_lexer         *ft_lexer(char *input, t_tools *tool);
void			print_tokens(t_lexer *head);
t_simple_cmds   *group_command(t_lexer **lexer);
int             check_closed_quotes(char *input);
void            print_cmd(t_simple_cmds **head);
void	        lstdelone_lexer(t_lexer *lst, void (*del)(void *));
void	        lstclear_lexer(t_lexer **lst, void (*del)(void *));
void	        lstdelone_cmds(t_simple_cmds *lst, void (*del)(void *));
void	        lstclear_cmds(t_simple_cmds **lst, void (*del)(void *));
char	        **dup_env(char **tab);
void	        *free_tab(char **tab, int j);
int             ft_istoken(int c);
t_tokens        chose_token(char *str);
void            handle_signal();

#endif
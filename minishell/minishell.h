/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:38:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/06 00:02:49 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer/lexer.h"
# include "parser/parser.h"
# include "expander/expander.h"
# include "builtins/builtins.h"
# include "executor/exec.h"
# include "libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_tokens
{
	WORD = 1,
	PIPE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT
}							t_tokens;

typedef struct s_lexer
{
	char					*str;
	t_tokens				token;
	int						i;
	struct s_lexer			*next;
	struct s_lexer			*prev;
}							t_lexer;

typedef struct s_tools
{
	char					**paths;
	char					*path;
	char					*cmd;
	char					**envp;
	int						*pid;
	char					*input;
	char					**inputs;
}							t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						fd_in;
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}							t_simple_cmds;

t_lexer						*new_token(char *str, t_tokens token, int i);
t_lexer						*ft_lexer(char *input, t_tools *tool);
void						print_tokens(t_lexer *head);
t_simple_cmds				*group_command(t_lexer **lexer);
void						print_cmd(t_simple_cmds **head);
void						lstdelone_lexer(t_lexer *lst, void (*del)(void *));
void						lstclear_lexer(t_lexer **lst, void (*del)(void *));
void						lstdelone_cmds(t_simple_cmds *lst,
								void (*del)(void *));
void						lstclear_cmds(t_simple_cmds **lst,
								void (*del)(void *));
char						**dup_env(char **tab);
void						*free_tab(char **tab, int j);
int							ft_istoken(int c);
t_tokens					chose_token(char *str);
void						handle_signal(void);
void						lstclear_tools(t_tools *tools);
int							init_tool(t_tools **tools, char **env);
void						ft_error(t_simple_cmds *cmd, t_lexer *lexer,
								t_tools *tools);
void						reset_tool(t_tools **tools);
void						lstclear_tools_two(t_tools *tools);
int							cmd_not_found(char *str);
void						lstclear_all(t_lexer **lexer, t_simple_cmds **cmds,
								t_tools *tools);

typedef struct s_global
{
	int						in_cmd;
	int						stop_heredoc;
	int						error_num;
	int						in_heredoc;
	int						in_child;
}							t_global;

extern t_global				g_global;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:30 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 19:05:13 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

int		one_command(t_simple_cmds *head, t_tools *tools, t_lexer *lexer);
char	*find_path(char **env);
char	*get_cmd(t_simple_cmds *cmd, t_tools *tools);
void	fill_cmd_heredoc(t_simple_cmds *curr, t_tools *tools);
void	heredoc(char *filename, t_lexer *curr, t_tools *tools);
char	*create_filename(void);
int		ft_whitespaces(char c);
int		multiple_commands(t_simple_cmds **head, t_tools *tools);
int		wait_process(t_tools *tools, t_simple_cmds **head);
int		dup_two_cmd(t_simple_cmds *curr, int pipes[2], int fd_in);
int		handle_cmd(t_simple_cmds *curr, t_tools *tools);
int		ft_check_heredoc(t_tools *tools, t_simple_cmds *cmd, int pipes[2]);
int		ft_fork(t_tools *tools, t_simple_cmds *curr, int pipes[2], int fd_in);
int		check_append(t_lexer *redir);
int		check_infile(char *file);
int		check_redir(t_simple_cmds *cmd);
int		check_outfile(t_lexer *redir);
void	free_child(t_tools **tools);
void	fill_tools_param(t_simple_cmds *curr, t_tools *tools);

#endif
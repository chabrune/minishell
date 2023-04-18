/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:30 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/18 20:24:50 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

int		one_command(t_simple_cmds **head, t_tools *tools);
char	*find_path(char **env);
char	*get_cmd(t_simple_cmds *cmd, t_tools *tools);
int		redir_is_fun(t_simple_cmds **head);
void	fill_cmd_heredoc(t_simple_cmds *curr);
void	heredoc(char *filename, t_lexer *curr);
char	*create_filename(void);
char	*get_word_after_hd(char *line);
int		ft_whitespaces(char c);
int		multiple_commands(t_simple_cmds **head, t_tools *tools);
int		child_process(t_simple_cmds *curr, t_tools *tools, int fd_in);
int		wait_process(t_tools *tools, t_simple_cmds **head);
int		dup_cmd(t_simple_cmds *curr, int fd_in, int pipes[2], t_tools *tools);
int		handle_cmd(t_simple_cmds *curr, t_tools *tools);
int		ft_check_heredoc(t_tools *tools, t_simple_cmds *cmd, int pipes[2]);
int		ft_fork(t_tools *tools, t_simple_cmds *curr, int fd_in, int pipes[2]);

#endif
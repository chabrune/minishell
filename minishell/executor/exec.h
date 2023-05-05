/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:30 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/02 20:30:13 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

int		one_command(t_simple_cmds *head, t_tools *tools);
char	*find_path(char **env);
char	*get_cmd(t_simple_cmds *cmd, t_tools *tools);
void	fill_cmd_heredoc(t_simple_cmds *curr);
void	heredoc(char *filename, t_lexer *curr);
char	*create_filename(void);
char	*get_word_after_hd(char *line);
int		ft_whitespaces(char c);
int		multiple_commands(t_simple_cmds **head, t_tools *tools);
int		wait_process(t_tools *tools, t_simple_cmds **head);
int		dup_cmd(t_simple_cmds *curr, int fd_in, int pipes[2], t_tools *tools);
int		handle_cmd(t_simple_cmds *curr, t_tools *tools);
int		ft_check_heredoc(t_tools *tools, t_simple_cmds *cmd, int pipes[2]);
int		ft_fork(t_tools *tools, t_simple_cmds *curr, int fd_in, int pipes[2]);
int		check_append(t_lexer *redir);
int		check_infile(char *file);
int 	check_redir(t_simple_cmds *cmd);
int 	check_outfile(t_lexer *redir);


#endif
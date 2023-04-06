/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:30 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/06 15:26:34 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

int		one_command(t_simple_cmds **head, t_tools *tools);
char	*find_path(char **env);
char	*get_cmd(char **paths, char *cmd);
int		redir_is_fun(t_simple_cmds **head);
void	fill_cmd_heredoc(t_simple_cmds **head, char *input);
void	heredoc(char *filename, char *input);
char 	*create_filename();
char 	*get_word_after_hd(char *line);
int		ft_whitespaces(char c);
int		multiple_commands(t_simple_cmds **head, t_tools	*tools);
int		child_process(t_simple_cmds *curr, t_tools *tools, t_simple_cmds **head, int **pipes, int *i);
void	parent_process(int **pipes, int *pids);


#endif
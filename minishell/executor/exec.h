/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:39:30 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/01 13:41:44 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

int		one_command(t_simple_cmds **head, t_tools *tools);
char	*find_path(char **env);
char	*get_cmd(char **paths, char *cmd);
int		redir_is_fun(t_simple_cmds **head);
void	fill_cmd_heredoc(t_simple_cmds **head);
void	heredoc(char *filename);
char 	*create_filename();


#endif
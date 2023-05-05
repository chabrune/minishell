/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:10:13 by emuller           #+#    #+#             */
/*   Updated: 2023/05/06 00:19:02 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

void	fill_var_content(t_simple_cmds *cmd, int i, int j, char **var_content);
void	add_lines_to_env(t_tools *tools, char **var_name, char **var_content);
int		var_name_is_new(t_tools *tools, char *var);
int		fill_var_name(t_simple_cmds *cmd, char **var_name, int i);
int		count_var(t_simple_cmds *cmd);
void	print_export(t_tools *tools);
void	choose_bultins_one(t_tools *tools, t_simple_cmds *cmd, t_lexer *lexer);
void	choose_bultins_multiple(t_tools *tools, t_simple_cmds *cmds);
int		is_builtins(t_simple_cmds *cmds);
void	my_pwd(t_tools *tools);
void	my_echo(t_simple_cmds *cmd);
void	my_env(t_tools *tools, t_simple_cmds *cmd);
void	my_cd(t_tools *tools, t_simple_cmds *cmds);
void	my_export(t_tools *tools, t_simple_cmds *cmd);
void	my_unset(t_tools *tools, t_simple_cmds *cmd);
void	my_exit(t_tools *tools, t_simple_cmds *cmds, t_lexer *lexer);
void	*free_old_env(char **tab);
int		builtins_to_fork(t_simple_cmds *cmds);
void	choose_builtins_one_split(t_simple_cmds *cmds, t_tools *tools);
void	choose_builtins_one_split_two(t_simple_cmds *cmds, t_tools *tools,
			t_lexer *lexer);

#endif
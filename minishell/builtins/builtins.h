/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:10:13 by emuller           #+#    #+#             */
/*   Updated: 2023/05/02 17:09:50 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

void	choose_bultins_one(t_tools *tools, t_simple_cmds *cmd);
void	choose_bultins_multiple(t_tools *tools, t_simple_cmds *cmds);
int		is_builtins(t_simple_cmds *cmds);
void	my_pwd(t_tools *tools);
void	my_echo(t_simple_cmds *cmd);
void	my_env(t_tools *tools, t_simple_cmds *cmd);
void	my_cd(t_tools *tools, t_simple_cmds *cmds);
void	my_export(t_tools *tools, t_simple_cmds *cmd);
void	my_unset(t_tools *tools, t_simple_cmds *cmd);
void	*free_old_env(char **tab);
int     builtins_to_fork(t_simple_cmds *cmds);

#endif
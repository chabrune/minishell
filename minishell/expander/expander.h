/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:01:42 by emuller           #+#    #+#             */
/*   Updated: 2023/04/01 13:41:10 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"

char    *expander(t_tools *tools, char *str);
char	*expand_str(char *str, char **var_name, char **var_content, int count);
char	*find_var_name(t_tools *tools, char *str, int dollar_pos);
int		name_exist(t_tools *tools, char *str, int n);
char    *coupe_le_debut(char *env);
char   *find_var_env(t_tools *tools, char *var_name);

#endif
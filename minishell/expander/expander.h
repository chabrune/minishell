/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:01:42 by emuller           #+#    #+#             */
/*   Updated: 2023/03/26 17:36:33 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"

char    *expander(t_tools *tools, char *str);
char	*expand_str(char *str, char *var_name, char *var_content);
char	*find_var_name(t_tools *tools, char *str);
int		name_exist(t_tools *tools, char *str, int n);
char    *coupe_le_debut(char *env);
char   *find_var_env(t_tools *tools, char *var_name);

#endif
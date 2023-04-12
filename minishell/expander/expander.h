/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:01:42 by emuller           #+#    #+#             */
/*   Updated: 2023/04/02 12:40:14 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"

char	*expander(t_tools *tools, char *str);
char	*expand_str(int nb_dollar, char *result, char *str, t_tools *tools);
char	*find_var_name(char *str, int dollar_pos);
char	*coupe_le_debut(char *env);
char	*find_var_env(t_tools *tools, char *var_name);
int		count_dollar(char *str);
int		check_var_name_exit(char *var_name, t_tools *tools);
int		find_len_result(char *str, char **var_name, char **var_content,
			int count);
char	*copy_var_name(int pos, char *str);

#endif
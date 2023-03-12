/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:16:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/03/12 17:34:37 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

char            **lexer_to_str_array(t_lexer *curr, t_lexer *stop, int *redir);
t_simple_cmds   *group_command(t_lexer **lexer);
void            add_redir_to_cmd(t_simple_cmds *head, int num_redirections);
void            print_t_lexer_list(t_simple_cmds *head);
void            find_redir(t_simple_cmds **head, t_lexer **lexer);
int             cmp(int token, int data_ref);
void            ft_list_remove_if(t_lexer **begin_list, int data_ref, int (*cmp)(int, int));
t_simple_cmds   *new_node();
void			add_back(t_simple_cmds **head, t_simple_cmds *new);
void			print_cmd(t_simple_cmds **head);



#endif
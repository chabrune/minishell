/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:16:17 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/14 13:43:59 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

char			**lexer_to_str_array(t_lexer *curr, t_lexer *stop, int *redir, t_lexer **head);
t_simple_cmds	*group_command(t_lexer **lexer);
void			print_t_lexer_list(t_simple_cmds *head);
void			del_node(t_lexer **head, t_lexer *delone);
t_lexer			*init_redir(t_lexer *curr);
void			add_node_redir(t_simple_cmds *curr, t_lexer *redir);
void			add_redir(t_simple_cmds **head, t_lexer **lexer);
void			find_redir(t_simple_cmds **head, t_lexer **lexer);
t_simple_cmds	*new_node(void);
void			add_back(t_simple_cmds **head, t_simple_cmds *new);
void			print_cmd(t_simple_cmds **head);
int				count_cmd(t_simple_cmds **head);
void			last_lexer_to_strs_cmd(t_lexer **headlex,
					t_simple_cmds **headcmd);

#endif
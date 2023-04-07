/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:18:15 by emuller           #+#    #+#             */
/*   Updated: 2023/04/07 18:06:54 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

int 		check_closed_quotes(char *input);
t_lexer		*new_token(char *str, t_tokens token, int i);
int			ft_isspace(int c);
int			ft_istoken(int c);
t_tokens 	chose_token(char *str);
char     	*fill_buffer_quote(int *i, char *input, int c, t_tokens *token);
char    	*fill_buffer_word(int *i, char *input, t_tokens *token);
char    	*fill_buffer_meta(int *i, char *input, t_tokens *token);
t_lexer 	*ft_lexer(char *input, t_tools *tools);

#endif
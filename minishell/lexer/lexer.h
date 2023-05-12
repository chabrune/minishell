/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:18:15 by emuller           #+#    #+#             */
/*   Updated: 2023/05/12 15:19:46 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

typedef struct s_simple_cmds	t_simple_cmds;
typedef struct s_lexer			t_lexer;
typedef struct s_tools			t_tools;
typedef enum s_tokens			t_tokens;

t_lexer							*new_token(char *str, t_tokens token, int i);
int								ft_isspace(int c);
int								ft_istoken(int c);
t_tokens						chose_token(char *str);
char							*fill_buffer_quote(int *i, char *input, int c,
									t_tokens *token);
char							*fill_buffer_word(int *i, char *input,
									t_tokens *token);
char							*fill_buffer_meta(int *i, char *input,
									t_tokens *token);
t_lexer							*ft_lexer(char *input, t_tools *tools);
void							fill_buffer_word_two(char *input, int *i,
									int *j);
void							lexer_list(t_lexer **tail, t_lexer **head,
									t_lexer **new);
int								check_pipe(t_lexer *lexer);
t_lexer							*ft_lstlast_lexer(t_lexer *lst);
void							ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);

#endif

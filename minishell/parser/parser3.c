/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:16:49 by chabrune          #+#    #+#             */
/*   Updated: 2023/04/14 13:51:08 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	find_redir(t_simple_cmds **head, t_lexer **lexer)
{
	add_redir(head, lexer);
	// if (*lexer)
	// 	last_lexer_to_strs_cmd(lexer, head);
}

int	count_cmd(t_simple_cmds **head)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

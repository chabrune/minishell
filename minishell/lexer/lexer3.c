/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:36:16 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 17:32:01 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_pipe(t_lexer *lexer)
{
	t_lexer *tmp;
	int i;
	int j;

	j = 0;
	i = 0;
	tmp = lexer;
	if (tmp->token == PIPE)
	{
		g_global.error_num = 258;
		ft_putendl_fd("bash: syntax erreur", 2);
		return (1);
	}
	while (tmp)
	{
		if (tmp->token == PIPE && tmp->next == NULL)
		{
			g_global.error_num = 258;
			ft_putendl_fd("bash: syntax erreur", 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
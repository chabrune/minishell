/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:36:16 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/09 16:39:59 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_pipe(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (!tmp)
		return (0);
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

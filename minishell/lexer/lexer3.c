/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:36:16 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 16:17:39 by chabrune         ###   ########.fr       */
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
	if(tmp->token == PIPE)
	{
		error_num = 258;
		ft_putendl_fd("lolbash: syntax erreur", 2);
		return (1);
	}
	while(tmp)
	{
		if(tmp->token == PIPE && tmp->next == NULL)
		{
			error_num = 258;
			ft_putendl_fd("mdrbash: syntax erreur", 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
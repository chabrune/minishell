/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:21:44 by emuller           #+#    #+#             */
/*   Updated: 2023/04/07 18:06:40 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int check_closed_quotes(char *input)
{
    int i;
    int single_quote;
    int double_quote;

    i = 0;
    single_quote = 0;
    double_quote = 0;
    while (input[i])
    {
        if (input[i] == 39)
            single_quote++;
        else if (input[i] == 34)
            double_quote++;
        i++;
    }
    if (single_quote % 2 != 0 || double_quote % 2 != 0)
        return (1);
    return (0);
}

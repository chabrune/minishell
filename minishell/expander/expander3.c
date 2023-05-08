/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:34:35 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 15:53:23 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*replace_name_with_content(char *str, char **var_name,
		char **var_content, int count)
{
	char	*result;
	int		i;
	int		k;
	int		l;

	l = -1;
	k = 0;
	i = 0;
	if (!var_content || !var_name)
		return (str);
	result = ft_calloc(find_len_result(str, var_name, var_content, count),
						sizeof(char));
	while (++l <= count)
	{
		replace_name_with_content_utils(&str, &result, &k, &i);
		if (str[k] == '$' && (ft_isalnum(str[k + 1]) || str[k + 1] == '_'
				|| str[k + 1] == '?'))
			k = k + ft_strlen(var_name[l]) + 1;
		replace_name_with_content_utils2(&var_content, &result, &l, &i);
		while (str[k] && str[k] != '$')
			result[i++] = str[k++];
	}
	return (result);
}

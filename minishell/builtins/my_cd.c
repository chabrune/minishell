/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:19:46 by emuller           #+#    #+#             */
/*   Updated: 2023/03/12 14:08:04 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

void	my_cd(t_tools *tools, t_simple_cmds *cmds)
{
	char    *s;
    int     i;
    int     check_err;

    i = -1;
	while (tools->envp[++i])
        if (ft_strncmp(tools->envp[i], "HOME=", 5) == 0)
            s = tools->envp[i];
	if (!(cmds->str[1]))
		check_err = chdir(s + 5); //Il faut changer le pwd et le old pwd dans env
	else if (cmds->str[1][0] == '/')
		check_err = chdir(s + 4);
	else 
		// chemin reatif
    if (check_err == -1)
        ft_putendl_fd("No such file or directory", 2);
}

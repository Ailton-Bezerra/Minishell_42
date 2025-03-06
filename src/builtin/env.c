/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:47:52 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/06 15:57:33 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env *env_list, char **cmd)
{
	int		i;
	
	i = 0;
	if (cmd[1])
		ft_export(env_list, cmd[1]);
	while (i < env_list->count)
	{
		printf("%s\n", env_list->var[i]);
		i++;
	}
}

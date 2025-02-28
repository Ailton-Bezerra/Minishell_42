/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:47:52 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/28 10:40:14 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env_list *env_list)
{
	int	i;

	
	// if (get_minishell()->tokens->next == WORD && ft_strchr(tokens->next, "="))
	// 		export(env_list, tokens->next);
	i = 0;
	while (i < env_list->count)
	{
		printf("%s\n", env_list->var[i]);
		i++;
	}
}

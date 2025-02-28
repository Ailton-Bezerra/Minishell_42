/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:47:52 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/28 15:22:11 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env_list *env_list)
{
	int	i;
	t_token		*tmp;
	
	get_ms()->exit_status = 0;
	i = 0;
	tmp = get_ms()->tokens;
	while (ft_strncmp(tmp->value , "env", 4))
		tmp = tmp->next;
	if (tmp->next && tmp->next->type == WORD)
		ft_export(env_list, tmp->next->value);
	while (i < env_list->count)
	{
		printf("%s\n", env_list->var[i]);
		i++;
	}
}

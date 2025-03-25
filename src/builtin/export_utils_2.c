/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:32:45 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/25 09:58:54 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*temp;

	if (!a || !b)
		return ;
	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env_list(t_env *env_list)
{
	int	i;
	int	j;

	if (!env_list || !env_list->copy || env_list->count < 2)
		return ;
	i = 0;
	while (i < env_list->count)
	{
		j = 0;
		while (j < env_list->count - i - 1)
		{
			if (ft_strcmp(env_list->copy[j], env_list->copy[j + 1]) > 0)
				ft_swap(&env_list->copy[j], &env_list->copy[j + 1]);
			j++;
		}
		i++;
	}
}

void	ft_xp(t_env *env_list)
{
	int		i;

	env_list->copy = gc_malloc(sizeof(char *) * env_list->count);
	if (!env_list->copy)
		return ;
	i = 0;
	while (i < env_list->count)
	{
		env_list->copy[i] = ft_strdup(env_list->var[i]);
		i++;
	}
	if (!env_list)
		return ;
	sort_env_list(env_list);
	i = 0;
	while (i < env_list->count)
	{
		printf("declare -x %s\n", env_list->copy[i]);
		i++;
	}
}

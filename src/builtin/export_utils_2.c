/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:32:45 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/20 14:20:33 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

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

	if (!env_list || !env_list->var || env_list->count < 2)
		return ;
	i = 0;
	while (i < env_list->count)
	{
		j = 0;
		while (j < env_list->count - i - 1)
		{
			if (ft_strcmp(env_list->var[j], env_list->var[j + 1]) > 0)
				ft_swap(&env_list->var[j], &env_list->var[j + 1]);
			j++;
		}
		i++;
	}
}

void	ft_xp(t_env *env_list)
{
	int		i;

	if (!env_list)
		return ;
	sort_env_list(env_list);
	i = 0;
	while (i < env_list->count)
	{
		printf("declare -x %s\n", env_list->var[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:48:12 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/06 15:58:34 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_unset_args(t_env **env, const char *var)
{
	if (!env || !*env || !var || !*var)
	{
		ft_putstr_fd("unset: invalid argument\n", 2);
		return (0);
	}
	return (1);
}

static void	shift_env_var(t_env *curr, int i)
{
	int	j;

	j = i;
	while (j < curr->count - 1)
	{
		curr->var[j] = curr->var[j + 1];
		j++;
	}
	curr->var[curr->count - 1] = NULL;
	curr->count--;
}

static void	remove_env_var(t_env **env, const char *var)
{
	t_env	*curr;
	size_t		len;
	int			i;

	curr = *env;
	len = ft_strlen(var);
	// while (curr)
	// {
	i = 0;
	while (i < curr->count)
	{
		if (ft_strncmp(curr->var[i], var, len) == 0
			&& curr->var[i][len] == '=')
		{
			shift_env_var(curr, i);
			return ;
		}
		i++;
	}
	// 	curr = curr->next;
	// }
}

void	ft_unset(t_env **env, const char *var)
{
	get_ms()->exit_status = 0;
	if (!validate_unset_args(env, var))
		return ;
	remove_env_var(env, var);
}

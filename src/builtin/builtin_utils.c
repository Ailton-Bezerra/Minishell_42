/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:19:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/24 17:49:26 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_envp(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static t_env	*allocate_env_node(int count)
{
	t_env	*new;

	new = gc_malloc(sizeof(t_env));
	if (!new)
	{
		perror("Erro de alocação de memória");
		return (NULL);
	}
	new->var = gc_malloc(sizeof(char *) * (count + 1));
	if (!new->var)
	{
		perror("Erro de alocação de memória");
		return (NULL);
	}
	return (new);
}

static int	copy_envp_to_node(t_env *new, char **envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new->var[i] = ft_strdup(envp[i]);
		if (!new->var[i])
		{
			perror("Erro de alocação de memória");
			return (-1);
		}
		i++;
	}
	new->var[count] = NULL;
	new->count = count;
	return (0);
}

t_env	*init_env(char **envp)
{
	t_env	*new;
	int		count;

	count = count_envp(envp);
	new = allocate_env_node(count);
	if (!new)
		return (NULL);
	copy_envp_to_node(new, envp, count);
	return (new);
}

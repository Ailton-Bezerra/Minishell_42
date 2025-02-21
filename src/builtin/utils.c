/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:19:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/21 14:44:15 by ailbezer         ###   ########.fr       */
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

static t_env_list	*allocate_env_list(int count)
{
	t_env_list	*new;

	new = gc_malloc(sizeof(t_env_list));
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

static int	copy_envp_to_node(t_env_list *new, char **envp, int count)
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
	new->next = NULL;
	return (0);
}

t_env_list	*convert_envp_to_env_list(char **envp)
{
	t_env_list	*env_list;
	t_env_list	*current;
	t_env_list	*new;
	int			count;

	env_list = NULL;
	current = NULL;
	count = count_envp(envp);
	new = allocate_env_list(count_envp(envp));
	if (!new)
		return (NULL);
	if (copy_envp_to_node(new, envp, count) == -1)
		return (NULL);
	if (!env_list)
		env_list = new;
	else
		current->next = new;
	current = new;
	return (env_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:19:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/12 18:12:27 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*convert_envp_to_env_list(char **envp)
{
	t_env_list	*env_list;
	t_env_list	*current;
	t_env_list	*new;
	int			count;
	int			i;

	env_list = NULL;
	current = NULL;
	count = 0;
	while (envp[count])
		count++;
	new = malloc(sizeof(t_env_list));
	if (!new)
	{
		perror("Erro de alocação de memória");
		return (NULL);
	}
	new->var = malloc(sizeof(char *) * (count + 1));
	if (!new->var)
	{
		perror("Erro de alocação de memória");
		free(new);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		new->var[i] = ft_strdup(envp[i]);
		if (!new->var[i])
		{
			perror("Erro de alocação de memória");
			while (i-- > 0)
				free(new->var[i]);
			free_array(new->var);
			free(new);
			return (NULL);
		}
		i++;
	}
	new->var[count] = NULL;
	new->count = count;
	new->next = NULL;
	if (!env_list)
		env_list = new;
	else
		current->next = new;
	current = new;
	return (env_list);
}

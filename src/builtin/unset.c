/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:48:12 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/13 18:04:22 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_unset_args(t_env_list **env, const char *var)
{
	if (!env || !*env || !var || !*var)
	{
		ft_putstr_fd("unset: invalid argument\n", 2);
		return (0);
	}
	return (1);
}

static void	free_env(t_env_list *node)
{
	int	i;

	i = 0;
	while (i < node->count)
	{
		free(node->var[i]);
		i++;
	}
	free(node->var);
	free(node);
	return ;
}

static void	print_env_list(t_env_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		printf("Variável na lista: \n");
		while (i < env->count)
		{
			printf("  var[%d]: %s\n", i, env->var[i]);
			i++;
		}
		env = env->next;
	}
}

// static t_env_list	*get_last_node(t_env_list *env)
// {
// 	if (!env)
// 		return (NULL);
// 	while (env->next)
// 		env = env->next;
// 	return (env);
// }

static void	remove_env_var(t_env_list **env, const char *var)
{
	t_env_list	*curr;
	t_env_list	*prev;
	size_t		len;
	int			i;

	curr = *env;
	prev = NULL;
	len = ft_strlen(var);
	while (curr)
	{
		i = 0;
		while (curr->var[i])
		{
			printf("Comparando: '%s' com '%s'\n", curr->var[i], var);
			// printf("strncmp retorno: %d\n", ft_strncmp(curr->var[i], var, len));
			// printf("caractere seguinte: '%c'\n", curr->var[i][len]);
			if (ft_strncmp(curr->var[i], var, len) == 0
				&& curr->var[i][len] == '=')
			{
				printf("curr->var[%d]: '%s', var: '%s', len: %zu\n", i, curr->var[i], var, len);
				// printf("Caractere esperado '=' na posição %zu: '%c'\n", len, curr->var[i][len]);
				printf("Removendo variável: %s\n", curr->var[i]);
				if (prev)
					prev->next = curr->next;
				else
					*env = curr->next;
				free_env(curr);
				return ;
			}
			i++;
		}
		prev = curr;
		curr = curr->next;
	}
	printf("Variável não encontrada: %s\n", var);
}

void	ft_unset(t_env_list **env, const char *var)
{
	printf("Recebido para unset: %s\n", var);
	print_env_list(*env);
	if (!validate_unset_args(env, var))
		return ;
	remove_env_var(env, var);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:47:24 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/12 18:02:21 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	separate_key_and_value(const char *arg, char **key, char **value)
{
	char	*equal_sign;
	size_t	name_len;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	name_len = equal_sign - arg;
	*key = ft_strndup(arg, name_len);
	*value = ft_strdup(equal_sign + 1);
	if (!*key || !*value)
	{
		free_var(*key, *value);
		return (0);
	}
	return (1);
}

static int	find_env(t_env_list *env, const char *name)
{
	int	name_len;
	int	i;

	if (!env || !env->var)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->var[i], name, name_len) == 0
			&& env->var[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	update_var(t_env_list *env, int i, const char *arg)
{
	if (!env || !env->var || !arg)
		return (0);
	free(env->var[i]);
	env->var[i] = malloc(ft_strlen(arg) + 1);
	if (!env->var[i])
		return (0);
	ft_strlcpy(env->var[i], arg, ft_strlen(arg) + 1);
	return (1);
}

static int	add_new_var(t_env_list *env, const char *arg)
{
	char	**new_var;

	if (!env || !arg)
		return (0);
	new_var = ft_realloc(env->var, env->count * sizeof(char *),
			(env->count + 1) * sizeof(char *));
	if (!new_var)
		return (0);
	env->var = new_var;
	env->var[env->count] = malloc(ft_strlen(arg) + 1);
	if (!env->var[env->count])
		return (0);
	ft_strlcpy(env->var[env->count], arg, ft_strlen(arg) + 1);
	env->count++;
	return (1);
}

int	ft_export(t_env_list *env, char *arg)
{
	int		i;
	char	*key;
	char	*value;

	if (!check_valid_env_name(arg))
	{
		printf("nome da variavel invalido\n");
		return (1);
	}
	if (!separate_key_and_value(arg, &key, &value))
	{
		printf("nao foi possivel separar a key e o value\n");
		return (1);
	}
	i = find_env(env, key);
	free(key);
	free(value);
	if (i != -1)
	{
		if (!update_var(env, i, arg))
		{
			printf("nao foi possivel atualizar a variavel\n");
			return (1);
		}
	}
	else
	{
		if (!add_new_var(env, arg))
		{
			printf("nao foi possivel adicionar a variavel\n");
			return (1);
		}
	}
	return (0);
}

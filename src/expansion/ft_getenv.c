/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:32:10 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/06 15:57:33 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(const char *var)
{	
	char	*equal_sign;
	size_t	name_len;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (NULL);
	name_len = equal_sign - var;
	key = ft_strndup(var, name_len);
	value = ft_strdup(equal_sign + 1);
	if (!*key || !*value)
		return (NULL);
	return (value);
}

char	*ft_getenv(t_env *env, const char *name)
{
	int	name_len;
	int	i;

	if (!env || !env->var)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->var[i], name, name_len) == 0
			&& env->var[i][name_len] == '=')
			return (env->var[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:00:53 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/28 11:48:15 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_env_name(const char *arg, const char *cmd)
{
	int	i;

	if (!arg || *arg == '=' || ft_isdigit(*arg))
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": not an identifier\n", 2);
		return (0);
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '_')
		{
			i++;
			continue ;
		}
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
		{
			ft_putstr_fd((char *)cmd, 2);
			ft_putstr_fd(": not an identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_var(char *var_name, char *var_value)
{
	perror("Erro de alocação de memória");
	free(var_name);
	free(var_value);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
		return (NULL);
	new_ptr = gc_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
	}
	return (new_ptr);
}

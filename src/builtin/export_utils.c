/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:00:53 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/12 15:30:03 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_env_name(const char *arg)
{
	if (!arg || *arg == '=')
	{
		ft_putstr_fd("Error: identifier not valid\n", 2);
		return (0);
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
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

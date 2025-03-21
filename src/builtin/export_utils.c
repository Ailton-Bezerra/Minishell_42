/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:00:53 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/21 18:06:30 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_env(char c, int first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

int	check_valid_env_name(const char *arg, const char *cmd)
{
	int	i;
	// int debug;

	(void)cmd;

	if (!arg || *arg == '=' || ft_isdigit(*arg) || !is_valid_env(*arg, 1))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		get_ms()->exit_status = 1;
		return (0);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		// printf("%c\n", arg[i]);
		// debug = is_valid_env(arg[i], 0);
		// printf("%d\n", debug);
		if (!is_valid_env(arg[i++], 0))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd((char *)arg, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			get_ms()->exit_status = 1;
			return (0);
		}
	}
	return (1);
}

void	free_var(char *var_name, char *var_value)
{
	perror("Erro de alocação de memória");
	free(var_name);
	free(var_value);
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->var);
		free(temp);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:47:52 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/28 09:58:17 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_add_env_vars(t_env_list *env_temp, int ac, char **av)
{
	int		i;
	char	*equal_sign;

	i = 1;
	while (i < ac)
	{
		equal_sign = ft_strchr(av[i], '=');
		if (!equal_sign)
			break ;
		if (check_valid_env_name(av[i], "env"))
			ft_add_to_env(env_temp, av[i]);
		else
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd(": No such file or directory \n", 2);
			free_env_list(env_temp);
			exit(1);
		}
		i++;
	}
	if (i < ac)
	{
		exec_with_env(env_temp, av + i);
		free_env_list(env_temp);
		exit(1);
	}
}

void	ft_env(t_env_list *env_list, int ac, char **av)
{
	t_env_list	env_temp;

	copy_env_list(&env_temp, env_list);
	ft_add_env_vars(&env_temp, ac, av);
	print_env_list(&env_temp);
	free_env_list(&env_temp);
}

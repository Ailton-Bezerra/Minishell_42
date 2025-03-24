/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:23:19 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/23 18:09:48 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_args(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (!ft_isdigit(arg[i++]))
		{
			get_ms()->exit_status = 2;
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (0);
		}
	}
	return (1);
}

void	ft_exit(char **cmd)
{
	if (!cmd[1])
		exit(get_ms()->exit_status);
	if (!check_args(cmd[1]))
	{
		gc_cleanup();
		close_fds();
		rl_clear_history();
		exit((unsigned char)get_ms()->exit_status);
	}
	get_ms()->exit_status = ft_atoi(cmd[1]);
	if (cmd[2])
	{
		get_ms()->exit_status = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	gc_cleanup();
	close_fds();
	rl_clear_history();
	exit(get_ms()->exit_status);
}

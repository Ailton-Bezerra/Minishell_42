/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:23:19 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/07 17:20:49 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i++]))
			{
				get_ms()->exit_status = 2;
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				gc_cleanup();
				close_fds();
				rl_clear_history();
				exit(get_ms()->exit_status);		
			}
		}
		get_ms()->exit_status = ft_atoi(cmd[1]);
	}
	gc_cleanup();
	close_fds();
	rl_clear_history();
	exit(get_ms()->exit_status);
}

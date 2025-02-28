/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:23:19 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/28 10:54:54 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **cmd)
{
	int	exit_cmd;

	exit_cmd = 0;
	if (cmd[1])
		exit_cmd = ft_atoi(cmd[1]);
	gc_cleanup();
	close_fds();
	rl_clear_history();
	exit(exit_cmd);
}

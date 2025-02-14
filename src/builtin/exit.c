/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:23:19 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/14 12:30:17 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *cmd)
{
	int	exit_cmd;

	if (ft_strncmp(cmd[0], "exit", 4) == 0)
	{
		exit_cmd = 0;
		if (ft_strlen(cmd) > 4)
			exit_cmd = ft_atoi(cmd + 5);
	}
	exit(exit_cmd);
}

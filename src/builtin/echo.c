/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:46:08 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/24 16:28:10 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_flag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-' && arg[1] != '\0')
	{
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **cmd)
{
	int		i;

	i = 1;
	get_ms()->exit_status = 0;
	if (cmd[1] && check_flag(cmd[1]))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (i == 1 || !check_flag(cmd[1]))
		ft_putchar_fd('\n', 1);
}

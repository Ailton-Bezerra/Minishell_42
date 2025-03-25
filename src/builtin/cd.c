/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:46:28 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/25 12:31:45 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(char **cmd)
{
	const char	*path;

	get_ms()->exit_status = 0;
	path = getenv("HOME");
	if (!cmd[1] || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
	{
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
	}
	else
		path = cmd[1];
	if (cmd[2] != NULL)
	{
		get_ms()->exit_status = 1;
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	if (chdir(path) != 0)
	{
		get_ms()->exit_status = 1;
		perror ("cd");
	}
}

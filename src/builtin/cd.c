/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:46:28 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/25 17:57:05 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_not_found(char **cmd)
{
	if (cmd[0][2] != '\0')
	{
		get_ms()->exit_status = 127;
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

static const char	*validate_cmd(char **cmd)
{
	const char	*path;

	get_ms()->exit_status = 0;
	path = getenv("HOME");
	if (!cmd[1] || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
	{
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else
		path = cmd[1];
	if (cmd[2] != NULL)
	{
		get_ms()->exit_status = 1;
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (NULL);
	}
	return (path);
}

void	ft_cd(char **cmd)
{
	const char	*path;

	path = validate_cmd(cmd);
	if (!path)
		return ;
	if (cd_not_found(cmd))
		return ;
	if (chdir(path) != 0)
	{
		get_ms()->exit_status = 1;
		perror ("cd");
	}
}

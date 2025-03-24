/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:31:58 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/24 16:00:38 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_directories(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
	{
		perror("Error: envp is NULL");
		return (NULL);
	}
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*get_path(char *cmd, char **envp)
{
	char	**valid_path;
	char	*fullpath;
	char	*part_path;
	int		i;

	valid_path = get_directories(envp);
	if (valid_path == NULL)
		return (NULL);
	i = 0;
	while (valid_path[i])
	{
		part_path = ft_strjoin(valid_path[i], "/");
		fullpath = ft_strjoin(part_path, cmd);
		if (access(fullpath, F_OK | X_OK) == 0)
			return (fullpath);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
		return (ft_strdup(cmd));
	return (get_path(cmd, envp));
}



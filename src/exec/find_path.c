/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:31:58 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/11 15:54:19 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_directories(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
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
		free(part_path);
		if (access(fullpath, F_OK | X_OK) == 0)
		{
			free_split(valid_path);
			return (fullpath);
		}
		free(fullpath);
		i++;
	}
	free_split(valid_path);
	return (NULL);
}

void	execute(char *av, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], envp);
	i = 0;
	if (path == NULL)
	{
		while (cmd[i])
			free (cmd[i++]);
		free (cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

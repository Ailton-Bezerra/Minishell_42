/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:31:58 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/19 10:49:38 by cabo-ram         ###   ########.fr       */
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

// void	execute(char *av, char **envp)
// {
// 	char	**cmd;
// 	char	*path;
// 	int		i;

// 	cmd = ft_split(av, ' ');
// 	path = get_path(cmd[0], envp);
// 	i = 0;
// 	if (path == NULL)
// 	{
// 		while (cmd[i])
// 			free (cmd[i++]);
// 		free (cmd);
// 		error();
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 		error();
// }

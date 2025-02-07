/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:52:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/07 18:41:18 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

void	execute_builtin(char **cmd)
{
	int		i;
	char	cwd[1024];

	i = 1;
	if (!ft_strncmp(cmd[0], "echo", 4))
	{
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (!ft_strncmp(cmd[0], "pwd", 3))
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
	}
}

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

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

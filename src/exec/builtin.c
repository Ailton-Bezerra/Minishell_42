/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:52:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/10 17:32:30 by cabo-ram         ###   ########.fr       */
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

void	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_cd(char **cmd)
{
	if (!cmd[1])
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd");
		else
		{
			if (chdir(cmd[1]) != 0)
				perror("cd");
		}
	}
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
}

// void	ft_export(char **cmd)
// {

// }

// void	ft_unset(char **cmd)
// {

// }

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	execute_builtin(char **cmd, char **envp)
{
	if (!cmd[0])
		return ;
	if (!ft_strncmp(cmd[0], "echo", 4))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		ft_cd(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		ft_pwd();
	// else if (!ft_strncmp(&cmd[0], "export", 6))
	// 	ft_export(cmd);
	// else if (!ft_strncmp(cmd[0], "unset", 5))
	// 	ft_unset(cmd);
	else if (!ft_strncmp(cmd[0], "env", 3))
		ft_env(envp);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		exit(EXIT_SUCCESS);
}

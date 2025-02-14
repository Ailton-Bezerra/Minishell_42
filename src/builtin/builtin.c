/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:52:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/14 12:30:34 by cabo-ram         ###   ########.fr       */
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

void	execute_builtin(char **cmd, t_env_list *env_list)
{
	if (!cmd[0])
		return ;
	if (!ft_strncmp(cmd[0], "echo", 4))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		ft_cd(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd[0], "export", 6))
	{
		if (cmd[1])
			ft_export(env_list, cmd[1]);
		else
			ft_export(env_list, NULL);
	}
	else if (!ft_strncmp(cmd[0], "unset", 5))
	{
		if (cmd[1])
			ft_unset(&env_list, cmd[1]);
	}
	else if (!ft_strncmp(cmd[0], "env", 3))
		ft_env(env_list);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		ft_exit(cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:52:56 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/23 15:47:05 by ailbezer         ###   ########.fr       */
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

void	execute_builtin(char **args, t_env *env_list)
{
	// int	*status;
	
	// status = &get_ms()->exit_status;
	// print_cmd_list(get_ms()->cmd_list);
	// if (!redirect_fds(get_ms()->cmd_list))
	// 	return ;
	if (!args[0])
		return ;
	if (!ft_strncmp(args[0], "echo", 4))
		ft_echo(args);
	else if (!ft_strncmp(args[0], "cd", 2))
		ft_cd(args);
	else if (!ft_strncmp(args[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(args[0], "export", 6))
		ft_export(env_list, args[1]);
	else if (!ft_strncmp(args[0], "unset", 5))
	{
		if (args[1])
			ft_unset(&env_list, args[1]);
	}
	else if (!ft_strncmp(args[0], "env", 3))
		ft_env(env_list, args);
	else if (!ft_strncmp(args[0], "exit", 4))
		ft_exit(args);
}

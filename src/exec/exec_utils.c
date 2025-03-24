/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:47:30 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/24 16:29:14 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_for_children(void)
{
	int	i;
	int	status;
	int	count;
	
	i = 0;
	count = get_ms()->count_pids;
	while (i < count)
	{
		waitpid(get_ms()->child_pids[i], &status, 0);
		if (WIFEXITED(status))
			get_ms()->exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	exec_external(t_command *cmd)
{
	int	flag;
	
	if (!cmd->path)
	{
		print_error(cmd->args[0]);
		clear_all();
		exit(127);
	}
	if (execve(cmd->path, cmd->args, get_ms()->env_list->var) == -1)
	{
		perror("execve error");
		if (access(cmd->args[0], F_OK) < 0)
			flag = 127;
		else if (access(cmd->args[0], X_OK) == 0)
			flag = 126;
		else
			flag = 126;
		clear_all();
		exit(flag);
	}
}

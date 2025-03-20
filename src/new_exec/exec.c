/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:57:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/20 18:00:07 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void execute_command(t_command *cmd)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		redirect_pipes(cmd);
		close_pipes(get_ms()->cmd_list, cmd);
		if (!ft_strncmp(cmd->path, "builtin", 8))
			execute_builtin(cmd->args, get_ms()->env_list);
		else
			exec_external(cmd);
	}
	else
		get_ms()->child_pids[get_ms()->count_pids++] = pid;
}

void	cmd_pipeline(t_command *cmd_list)
{
	t_command	*tmp;
	
	tmp = cmd_list;
	get_ms()->count_pids = 0;
	get_ms()->child_pids = malloc(sizeof(int) * (count_pipes(get_ms()->tokens) + 1));
	creat_pipes(cmd_list);
	while (tmp)
	{
		execute_command(tmp);
		tmp = tmp->next;
	}
	close_pipes(get_ms()->cmd_list, NULL);
	wait_for_children();
}

void	exec(void)
{
		t_command	*cmd_list;
	
		cmd_list = creat_cmd_list(get_ms()->tokens);
		get_ms()->cmd_list = cmd_list;
		// print_cmd_list(cmd_list);
		if (cmd_list->path && !ft_strncmp(cmd_list->path, "builtin", 8)
			&& !cmd_list->pipe_in && !cmd_list->pipe_out)
			execute_builtin(cmd_list->args, get_ms()->env_list);
		else
			cmd_pipeline(cmd_list);
}

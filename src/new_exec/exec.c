/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:57:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/21 19:43:10 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void execute_command(t_command *cmd)
{
	int	pid;
	
	pid = fork();
	cmd_signal();
	if (pid == 0)
	{
		redirect_pipes(cmd);
		close_pipes(get_ms()->cmd_list, cmd);
		// if (redirects(get_ms()->tokens, get_ms()->env_list))
		// 	exit(1); 
		if (builtin(cmd->args[0]))
		{
			execute_builtin(cmd->args, get_ms()->env_list);
			exit (get_ms()->exit_status);
		}
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
		if (builtin(cmd_list->args[0])
			&& !cmd_list->pipe_in && !cmd_list->pipe_out)
			execute_builtin(cmd_list->args, get_ms()->env_list);
		else
			cmd_pipeline(cmd_list);
}

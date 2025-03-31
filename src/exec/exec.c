/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:57:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/28 15:38:46 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_cmd_io(t_command *cmd)
{
	if (cmd->infile && cmd->infile_fd < 0)
	{
		clear_all();
		exit(1);
	}
	if (cmd->outfile && cmd->outfile_fd < 0)
	{
		clear_all();
		exit(1);
	}
}

static void	execute_command(t_command *cmd, int pid)
{
	pid = fork();
	cmd_signal();
	if (pid == 0)
	{
		redirect_pipes(cmd);
		if (!redirect_fds(cmd))
		{
			clear_all();
			exit(1);
		}
		close_pipes(get_ms()->cmd_list, cmd);
		close_redirects(cmd);
		check_cmd_io(cmd);
		if (builtin(cmd->args[0]))
		{
			execute_builtin(cmd->args, get_ms()->env_list);
			clear_all();
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
	int			pid;

	pid = 1;
	tmp = cmd_list;
	get_ms()->count_pids = 0;
	get_ms()->child_pids = gc_malloc(sizeof(int)
		* (count_pipes(get_ms()->tokens) + 1));
	creat_pipes(cmd_list);
	while (tmp)
	{
		execute_command(tmp, pid);
		tmp = tmp->next;
	}
	close_pipes(get_ms()->cmd_list, NULL);
	wait_for_children();
}

void	exec(void)
{
	t_command	*cmd_list;
	static int	cmd_index = 0;

	cmd_list = creat_cmd_list(get_ms()->tokens, &cmd_index);
	if (!cmd_list)
		return ;
	get_ms()->cmd_list = cmd_list;
	if (!cmd_list->args[0])
		return ;
	if ((builtin(cmd_list->args[0]) && !cmd_list->pipe_out
			&& (cmd_list->infile && ft_strncmp(cmd_list->infile, "error", 6)))
		|| (builtin(cmd_list->args[0]) && !cmd_list->pipe_out
			&& !cmd_list->infile && !cmd_list->outfile))
		execute_builtin(cmd_list->args, get_ms()->env_list);
	else
		cmd_pipeline(cmd_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:57:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/20 16:34:58 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void handle_redirections(t_command *cmd, int input, int output)
{
	if (cmd->pipe_in)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (cmd->pipe_out)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	if (input != -1)
		close(input);
	if (output != -1)
		close(output);
}

static void execute_command(t_command *cmd, int input, int output)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		handle_redirections(cmd, input, output);
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
	int			prev_pipe_in;
	int			output_fd;
	
	tmp = cmd_list;
	prev_pipe_in = -1;
	output_fd = -1;
	get_ms()->count_pids = 0;
	get_ms()->child_pids = malloc(sizeof(int) * (count_pipes(get_ms()->tokens) + 1));
	// creat_pipes(*cmd_list);
	while (tmp)
	{
		execute_command(tmp, prev_pipe_in, output_fd);
		tmp = tmp->next;
	}
	wait_for_children();
}

static void	exec_cmds(t_command *cmd_node, int is_builtin)
{
	if (is_builtin && !cmd_node->pipe_in && !cmd_node->pipe_out)
		execute_builtin(cmd_node->args, get_ms()->env_list);
	else
		cmd_pipeline(cmd_node);
	
}

void	exec(void)
{
		t_command	*cmd_list;
	
		cmd_list = creat_cmd_list(get_ms()->tokens);
		get_ms()->cmd_list = cmd_list;
		// print_cmd_list(cmd_list);
		if (cmd_list->path && !ft_strncmp(cmd_list->path, "builtin", 8) && !cmd_list->pipe_in && !cmd_list->pipe_out)
			exec_cmds(cmd_list, 1);
		else
			cmd_pipeline(cmd_list);
}

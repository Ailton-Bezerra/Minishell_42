/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:57:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/19 14:56:59 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_token *tokens)
{
	t_token	*tmp;
	int		count;

	tmp = tokens;
	count = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_command	*creat_cmd_list(t_token *tmp_token)
{
	t_command	*cmd_list;
	char		**args;
	int			pipe_in;
	int			pipe_out;
	int			cmd_qtd;

	pipe_in = 0;
	cmd_list = NULL;
	cmd_qtd = count_pipes(get_ms()->tokens) + 1;
	while (tmp_token)
	{
		pipe_out = (cmd_qtd - 1 > 0);
		args = prepare_command(tmp_token);
		append_cmd(args, &cmd_list, pipe_in, pipe_out);
		pipe_in++;
		while (tmp_token && tmp_token->type != PIPE)
			tmp_token = tmp_token->next;
		if (tmp_token)
		{
			tmp_token = tmp_token->next;
			cmd_qtd--;
		}
	}
	return (cmd_list);
}

void	exec_external(t_command *cmd_list)
{
	if (execve(cmd_list->path, cmd_list->args, get_ms()->env_list->var) == -1)
	{
		perror("execve error");
		gc_cleanup();
		close_fds();
		rl_clear_history();
		exit(127);
	}
}

void	exec_cmds(t_command *cmd_node, int is_builtin)
{
	int	pid;
	int	status;
	int	fd[2];
	
	pipe(fd);
	if(is_builtin)
		execute_builtin(cmd_node->args, get_ms()->env_list);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd_node->pipe_in)
				dup2(fd[0], STDIN_FILENO);
			if (cmd_node->pipe_out)
				dup2(fd[1], STDOUT_FILENO);
			exec_external(cmd_node);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, &status, 0);
	}
}

void	cmd_pipeline(t_command *cmd_list)
{
	t_command *tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if(!ft_strncmp(cmd_list->path, "builtin", 8))
			exec_cmds(tmp, 1);
		else
			exec_cmds(tmp, 0);
		tmp = tmp->next;
	}
}

void	exec(void)
{
	t_command	*cmd_list;

	cmd_list = creat_cmd_list(get_ms()->tokens);
	// print_cmd_list(cmd_list);
	cmd_pipeline(cmd_list);
}

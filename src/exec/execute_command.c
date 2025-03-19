/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/19 11:48:22 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_child_process(char *path, char **args, char **envp)
{
	if (execve(path, args, envp) == -1)
	{
		perror("execve error");
		gc_cleanup();
		close_fds();
		rl_clear_history();
		exit(127);
	}
}

static void	handle_external_command(char *cmd, char **args, char **t_env)
{
	char	*path;
	pid_t	pid;
	int		status;
		
	path = get_command_path(cmd, t_env);
	if (!path)
	{
		print_error(cmd);
		return ;
	}
	pid = fork();
	if (pid < 0)
		fork_error(path, args);
	else if (pid == 0)
		execute_child_process(path, args, t_env);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			get_ms()->exit_status = WEXITSTATUS(status);
	}
}

char	**prepare_command(t_token *tokens)
{
	int			arg_count;
	char		**args;

	if (!tokens || !tokens->value)
		return (NULL);
	arg_count = count_args(tokens);
	args = get_args(tokens, arg_count);
	if (!args)
		return (NULL);
	return (args);
}

void	execute_command(t_token *tokens, t_env *env_list, char **t_env)
{
	char		**args;
	char		*cmd;

	args = prepare_command(tokens);
	if (!args)
	{
		printf("Error: Arguments preparation failed\n");
		return ;
	}
	cmd = args[0];
	if (!cmd)
		return ;
	if (builtin(cmd))
		execute_builtin(args, env_list);
	else
	{
		cmd_signal();
		handle_external_command(cmd, args, t_env);
	}
}

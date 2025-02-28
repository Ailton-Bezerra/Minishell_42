/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/27 14:27:32 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_child_process(char *path, char **av, char **envp)
{
	if (execve(path, av, envp) == -1)
	{
		perror("execve error");
		// free(path);
		// free_array(av);
		gc_cleanup();
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
}

static void	handle_external_command(char *cmd, char **args, char **envp)
{
	char	*path;
	pid_t	pid;

	path = get_command_path(cmd, envp);
	if (!path)
	{
		print_error(cmd);
		// free_array(args);
		return ;
	}
	pid = fork();
	if (pid < 0)
		fork_error(path, args);
	else if (pid == 0)
		execute_child_process(path, args, envp);
	else
		waitpid(pid, NULL, 0);
	// free(path);
	// free_array(args);
}

static char	**prepare_command(t_token *tokens)
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

void	execute_command(t_token *tokens, t_env_list *env_list, char **envp)
{
	char		**args;
	char		*cmd;
	int			ac;
	char		*av;

	args = prepare_command(tokens);
	if (!args)
	{
		printf("Error: Arguments preparation failed\n");
		return ;
	}
	cmd = args[0];
	if (!cmd)
	{
		// free_array(args);
		return ;
	if (builtin(cmd))
		execute_builtin(args, env_list, ac, &av);
		// free_array(args);
	}
	else
		handle_external_command(cmd, args, envp);
}

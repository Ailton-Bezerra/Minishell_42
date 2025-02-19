/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/14 15:09:56 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_child_process(char *path, char **av, char **envp)
{
	if (execve(path, av, envp) == -1)
	{
		perror("execve error");
		free(path);
		free_array(av);
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
		free_array(args);
		return ;
	}
	pid = fork();
	if (pid < 0)
		fork_error(path, args);
	else if (pid == 0)
		execute_child_process(path, args, envp);
	else
		waitpid(pid, NULL, 0);
	free(path);
	free_array(args);
}

static char	**prepare_command(t_token *tokens, char **envp,
	t_env_list **env_list)
{
	int			arg_count;
	char		**args;

	*env_list = convert_envp_to_env_list(envp);
	if (!*env_list)
		return (NULL);
	if (!tokens || !tokens->value)
		return (NULL);
	arg_count = count_args(tokens);
	args = get_args(tokens, arg_count);
	return (args);
}

void	execute_command(t_token *tokens, char **envp)
{
	char		**args;
	char		*cmd;
	t_env_list	*env_list;

	args = prepare_command(tokens, envp, &env_list);
	if (!args)
		return ;
	cmd = args[0];
	if (!cmd)
	{
		free_array(args);
		return ;
	}
	if (builtin(cmd))
	{
		execute_builtin(args, env_list);
		free_array(args);
	}
	else
		handle_external_command(cmd, args, envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/12 16:35:09 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_command_path(char *cmd, char **envp)
{
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
		return (ft_strdup(cmd));
	return (get_path(cmd, envp));
}

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

static void	fork_error(char *path, char **args)
{
	perror("fork error");
	free(path);
	free_array(args);
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

void	execute_command(t_token *tokens, char **envp)
{
	int			arg_count;
	char		**args;
	char		*cmd;
	t_env_list	*env_list;

	printf("Converting envp to env_list\n");
	env_list = convert_envp_to_env_list(envp);
	if (!env_list)
		return ;
	printf("Checking tokens\n");
	if (!tokens || !tokens->value)
		return ;
	printf("Counting args\n");
	arg_count = count_args(tokens);
	printf("Getting args\n");
	args = get_args(tokens, arg_count);
	if (!args)
		return ;
	cmd = args[0];
	if (!cmd)
	{
		free_array(args);
		return ;
	}
	printf("Checking if builtin\n");
	if (builtin(cmd))
	{
		printf("Executing builtin\n");
		execute_builtin(args, env_list);
		free_array(args);
	}
	else
	{
		printf("Handling external command\n");
		handle_external_command(cmd, args, envp);
	}
}

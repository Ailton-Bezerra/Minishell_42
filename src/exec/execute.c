/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/10 18:30:19 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type == WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

static char	**get_args(t_token *tokens, int count)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("Error");
		return ;
	}
	while (tokens && tokens->type == WORD)
	{
		args[i] = ft_strdup(tokens->value);
		if (!args[i])
		{
			perror("Error");
			free_array(args);
			return ;
		}
		tokens = tokens->next;
		i++;
	}
	args[count] = NULL;
	return (args);
}

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
		perror("execve");
		free(path);
		free_array(av);
		exit(EXIT_FAILURE);
	}
}

void	execute_command(t_token *tokens, char **envp)
{
	pid_t	pid;
	int		arg_count;
	char	**args;
	char	*cmd;
	char	*path;

	if (!tokens || !tokens->value)
		return ;
	arg_count = count_args(tokens);
	args = get_args(tokens, arg_count);
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
		execute_builtin(args, envp);
		free_array(args);
		return ;
	}
	path = get_command_path(cmd, envp);
	if (!path)
	{
		ft_putstr_fd("Error: Missing argument\n", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		free_array(args);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(path);
		free_array(args);
		return ;
	}
	else if (pid == 0)
		execute_child_process(path, args, envp);
	else
		waitpid(pid, NULL, 0);
	free(path);
	free_array(args);
}

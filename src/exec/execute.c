/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:40 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/10 17:35:49 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	execute_command(t_token *tokens, char **envp)
{
	pid_t	pid;
	char	**args;
	int		i;
	t_token	*temp;
	char	*cmd;
	char	*path;

	if (!tokens || !tokens->value)
		return ;
	i = 0;
	temp = tokens;
	while (temp && temp->type == WORD)
	{
		i++;
		temp = temp->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
	{
		perror("Error");
		return ;
	}
	temp = tokens;
	i = 0;
	while (temp && temp->type == WORD)
	{
		args[i] = ft_strdup(temp->value);
		if (!args[i])
		{
			perror("Error");
			free_array(args);
			return ;
		}
		temp = temp->next;
		i++;
	}
	args[i] = NULL;
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
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
		path = ft_strdup(cmd);
	else
		path = get_path(cmd, envp);
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
	{
		if (execve(path, args, envp) == -1)
		{
			perror("execve");
			free(path);
			free_array(args);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, NULL, 0);
	free(path);
	free_array(args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:02:37 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/28 10:19:33 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_list(t_env_list *env_list)
{
	int	i;

	i = 0;
	while (i < env_list->count)
	{
		printf("%s\n", env_list->var[i]);
		i++;
	}
}

void	copy_env_list(t_env_list *dest, t_env_list *src)
{
	int	i;

	if (!dest || !src)
		return ;
	dest->count = src->count;
	dest->var = gc_malloc((src->count + 1) * sizeof(char *));
	if (!dest->var)
		return ;
	i = 0;
	while (i < src->count)
	{
		dest->var[i] = gc_malloc(ft_strlen(src->var[i]) + 1);
		if (!dest->var[i])
		{
			free_env_list(dest);
			return ;
		}
		ft_strlcpy(dest->var[i], src->var[i], ft_strlen(src->var[i]) + 1);
	}
	i++;
	dest->var[src->count] = NULL;
}

int	ft_add_to_env(t_env_list *env, const char *arg)
{
	char	**new_var;
	char	*new_entry;

	if (!env || !arg)
		return (0);
	new_entry = gc_malloc(ft_strlen(arg) + 1);
	if (!new_entry)
		return (0);
	ft_strlcpy(new_entry, arg, ft_strlen(arg) + 1);
	new_var = ft_realloc(env->var, (env->count + 1) * sizeof(char *),
			(env->count + 2) * sizeof(char *));
	if (!new_var)
	{
		gc_cleanup();
		return (0);
	}
	env->var = new_var;
	env->var[env->count] = new_entry;
	env->count++;
	env->var[env->count] = NULL;
	return (1);
}

void	exec_with_env(t_env_list *env, char **cmd)
{
	pid_t	pid;

	if (!cmd || !cmd[0])
		return ;

	pid = fork();
	if (pid < 0)
	{
		perror("env: fork");
		return ;
	}
	if (pid == 0)
	{
		execve(cmd[0], cmd, env->var);
		perror("env");
		exit(127);
	}
	waitpid(pid, NULL, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:38:43 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/15 16:08:33 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_command_path(char *cmd, char **envp)
{
	if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
		return (ft_strdup(cmd));
	return (get_path(cmd, envp));
}

void	fork_error(char *path, char **args)
{
	perror("fork error");
	free(path);
	free_array(args, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:38:43 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/23 16:36:07 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_command_path(char *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
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

t_token	*get_cmd_tokens(t_token *tokens)
{
	t_token	*cmd_tokens;

	cmd_tokens = tokens;
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	return (cmd_tokens);
}

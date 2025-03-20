/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:47:30 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/20 12:32:15 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void wait_for_children(void)
{
	int	i;
	int	status;
	int	count;
	
	i = 0;
	count = get_ms()->count_pids;
	while (i < count)
	{
		waitpid(get_ms()->child_pids[i], &status, 0);
		if (WIFEXITED(status))
			get_ms()->exit_status = WEXITSTATUS(status);
		i++;
	}
	free(get_ms()->child_pids);
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
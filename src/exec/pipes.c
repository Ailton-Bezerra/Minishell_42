/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:09:10 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/24 16:10:37 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	creat_pipes(t_command *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->pipe_out)
			pipe(cmd_list->pipe_fd);
		cmd_list = cmd_list->next;
	}
}

void	close_pipes(t_command *cmd_list, t_command *curr)
{
	while(cmd_list)
	{
		if (cmd_list != curr && cmd_list->pipe_out)
		{
			close(cmd_list->pipe_fd[0]);
			close(cmd_list->pipe_fd[1]);	
		}
		cmd_list = cmd_list->next;
	}
}

void	redirect_pipes(t_command *cmd)
{
	if (cmd->pipe_out)
	{
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
	}
	if (cmd->prev && cmd->prev->pipe_out)
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
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
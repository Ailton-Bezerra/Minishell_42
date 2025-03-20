/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:09:10 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/20 17:56:47 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	creat_pipes(t_command *cmd_list)
{
	t_command *tmp;
	
	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->pipe_out)
			pipe(tmp->pipe_fd);
		tmp = tmp->next;
	}
}

void 	close_pipes(t_command *cmd_list, t_command *curr)
{
	t_command *tmp;

	tmp = cmd_list;
	while(tmp)
	{
		if (tmp != curr && tmp->pipe_out)
		{
			close(tmp->pipe_fd[0]);
			close(tmp->pipe_fd[1]);	
		}
		tmp = tmp->next;
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
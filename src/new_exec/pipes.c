/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:09:10 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/20 15:13:53 by ailbezer         ###   ########.fr       */
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
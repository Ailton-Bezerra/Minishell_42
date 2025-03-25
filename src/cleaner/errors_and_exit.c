/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:36:14 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/25 17:28:01 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(void)
{
	int	i;

	i = 0;
	while (i <= 1024)
		close(i++);
}

void	print_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	exec_errors(t_command *cmd, int *flag)
{
	if (access(cmd->args[0], F_OK) < 0)
		{
			perror(" ");
			*flag = 127;
		}
		else if (access(cmd->args[0], X_OK) == 0)
		{
			ft_putstr_fd(" Is a directory\n", 2);
			*flag = 126;
		}
		else
		{
			*flag = 126;
			perror(" ");
		}
}

void	clear_all(void)
{
	gc_cleanup();
	close_fds();
	rl_clear_history();
}

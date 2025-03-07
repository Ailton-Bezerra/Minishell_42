/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:52:05 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/06 16:36:58 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_ctrl_c(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)info;
	(void)context;
	get_ms()->exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	receive_signal(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backslash;
 
	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ft_memset(&ctrl_backslash, 0, sizeof(ctrl_backslash));
	ctrl_c.sa_sigaction = handle_ctrl_c;
	ctrl_backslash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_backslash, NULL);
}

void	ctrl_c(int sig)
{
	(void)sig;
	get_ms()->exit_status = 130;
	write(1, "\n", 1);
}

void	ctrl_backslash(int sig)
{
	(void)sig;
	get_ms()->exit_status = 131;
	write(1, CYAN "Quit (core dumped)\n" END, 35);
}

void	cmd_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_backslash);
}

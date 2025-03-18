/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:57:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/11 13:36:37 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	count_pipes(t_token *tokens)
{
	t_token *tmp;
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

void exec(void)
{
	int		cmds;
	int		fd[2];
	int		i;
	int		pid;
	int		status;
	
	cmds = count_pipes(get_ms()->tokens) + 1;
	i = 0;
	if (pipe(fd) == -1)
	{
		perror("Error creating pipe");
		exit (EXIT_FAILURE);
	}
	while (i < cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error creating fork");
			exit (EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			t_token		*cmd_tokens;

			cmd_tokens = get_cmd_tokens(get_ms()->tokens);
			// dup2(input_fd, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close (fd[0]);
			close(fd[1]);
			execute_command(cmd_tokens, get_ms()->env_list, get_ms()->env_list->var);
		}
		close(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_ms()->exit_status = WEXITSTATUS(status);
}

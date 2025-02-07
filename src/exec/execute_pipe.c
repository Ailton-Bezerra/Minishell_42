/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:17:42 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/07 16:53:44 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipe(t_token *tokens, char **envp)
{
	int		fd[2];
	pid_t	pid;
	t_token	*cmd1;
	t_token	*cmd2;

	cmd1 = tokens;
	cmd2 = NULL;
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (!tokens)
	{
		execute_command(cmd1, envp);
		return ;
	}
	tokens->value = NULL;
	cmd2 = tokens->next;
	if (pipe(fd) == -1)
	{
		perror("Error");
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		return ;
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(cmd1, envp);
		free_tokens(cmd1);
		exit(1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_command(cmd2, envp);
		free_tokens(cmd2);
		waitpid(pid, NULL, 0);
	}
}

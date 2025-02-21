/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:17:42 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/20 12:34:02 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*find_and_create_pipe(t_token *tokens, int fd[2])
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens && pipe(fd) == -1)
	{
		perror("Error creating pipe");
		return (NULL);
	}
	return (tokens);
}

static void	child_process(t_token *cmd1, char **envp, int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_command(cmd1, envp);
	// free_tokens(cmd1);
	exit(1);
}

static void	parent_process(t_token *cmd2, char **envp, int fd[2], pid_t pid)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execute_command(cmd2, envp);
	waitpid(pid, NULL, 0);
}

static void	fork_and_execute(t_token *cmd1, t_token *cmd2, char **envp,
	int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error creating fork");
		return ;
	}
	else if (pid == 0)
		child_process(cmd1, envp, fd);
	else
		parent_process(cmd2, envp, fd, pid);
}

void	execute_pipe(t_token *tokens, char **envp)
{
	int		fd[2];
	t_token	*cmd1;
	t_token	*cmd2;
	t_token	*pipe_token;

	cmd1 = tokens;
	cmd2 = NULL;
	pipe_token = find_and_create_pipe(tokens, fd);
	if (!pipe_token)
	{
		execute_command(cmd1, envp);
		// gc_cleanup();
		return ;
	}
	tokens->value = NULL;
	cmd2 = tokens->next;
	fork_and_execute(cmd1, cmd2, envp, fd);
}

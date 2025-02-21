/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:17:42 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/21 14:47:27 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*find_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens)
		tokens = tokens->next;
	return (tokens);
}

void	child_process(t_token *tokens, char **envp, int input_fd,
	int fd[2])
{
	close (fd[0]);
	dup2(input_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	printf("Executing command in child process\n");
	execute_command(tokens, envp);
	gc_cleanup();
	// free_tokens(cmd1);
	exit(1);
}

void	parent_process(t_token *tokens, char **envp, int output_fd,
	int fd[2])
{
	t_token	*next_cmd;

	close(fd[1]);
	waitpid(-1, NULL, 0);
	if (tokens->next)
	{
		printf("Running next command in pipeline\n");
		next_cmd = find_pipe(tokens);
		run_pipeline(tokens->next, envp, fd[0], output_fd);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		printf("Executing final command in parent process\n");
		execute_command(tokens, envp);
	}
}

void	run_pipeline(t_token *tokens, char **envp, int input_fd,
	int output_fd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("Error creating pipe");
		exit (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error creating fork");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("Forked child process\n");
		child_process(tokens, envp, input_fd, fd);
	}
	else
	{
		printf("Forked parent process\n");
		parent_process(tokens, envp, output_fd, fd);
	}
}

void	process_pipes(t_token *tokens, char **envp)
{
	int		input_fd;
	int		output_fd;
	t_token	*pipe_token;

	pipe_token = find_pipe(tokens);
	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	if (!pipe_token)
	{
		printf("No pipe found, executing single command\n");
		execute_command(tokens, envp);
		// gc_cleanup();
		return ;
	}
	printf("Pipe found, running pipeline\n");
	run_pipeline(tokens, envp, input_fd, output_fd);
}

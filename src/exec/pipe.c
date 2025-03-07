/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:17:42 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/05 12:06:35 by cabo-ram         ###   ########.fr       */
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
	printf("Child process started\n");
	t_token		*cmd_tokens;
	t_env_list	*env_list;

	cmd_tokens = get_cmd_tokens(tokens);
	env_list = NULL;
	close (fd[0]);
	dup2(input_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_command(cmd_tokens, env_list, envp);
	printf("Child process finished\n");
	exit(EXIT_SUCCESS);
}

void	parent_process(t_token *tokens, char **envp, int output_fd,
	int fd[2])
{
	printf("Parent process started\n");
	t_token		*next_cmd;
	t_token		*cmd_tokens;
	t_env_list	*env_list;

	next_cmd = find_pipe(tokens);
	env_list = NULL;
	close(fd[1]);
	// waitpid(-1, NULL, 0);
	if (next_cmd)
	{
		printf("Running next command in pipeline\n");
		cmd_tokens = get_cmd_tokens(next_cmd);
		run_pipeline(cmd_tokens, envp, fd[0], output_fd);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		printf("Executing final command in parent process\n");
		execute_command(tokens, env_list, envp);
		waitpid(-1, NULL, 0);
	}
	printf("Parent process finished\n");
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

void	process_pipes(t_token *tokens, t_env_list *env_list, char **envp)
{
	int		input_fd;
	int		output_fd;
	t_token	*pipe_token;

	pipe_token = find_pipe(tokens);
	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	if (!pipe_token)
	{
		execute_command(tokens, env_list, envp);
		return ;
	}
	printf("Pipe found, running pipeline\n");
	run_pipeline(tokens, envp, input_fd, output_fd);
	while (waitpid(-1, NULL, 0) > 0);
}

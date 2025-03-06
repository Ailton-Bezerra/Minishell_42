/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:17:42 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/06 16:17:18 by ailbezer         ###   ########.fr       */
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
	t_token		*cmd_tokens;

	cmd_tokens = get_cmd_tokens(tokens);
	dup2(input_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close (fd[0]);
	close(fd[1]);
	execute_command(cmd_tokens, get_ms()->env_list, envp);
	gc_cleanup();
	close_fds();
	rl_clear_history();
	exit(1);
}

void	parent_process(t_token *tokens, char **envp, int output_fd,
	int fd[2])
{
	t_token		*next_cmd;
	t_token		*cmd_tokens;
	t_env	*env_list;

	next_cmd = find_pipe(tokens);
	env_list = NULL;
	close(fd[1]);
	if (next_cmd)
	{
		cmd_tokens = get_cmd_tokens(next_cmd);
		run_pipeline(cmd_tokens, envp, fd[0], output_fd);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_command(tokens, env_list, envp);
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
		child_process(tokens, envp, input_fd, fd);
	else
		parent_process(tokens, envp, output_fd, fd);
}

void	process_pipes(t_token *tokens, t_env *env_list, char **t_env)
{
	t_token	*pipe_token;
	
	int		input_fd;
	int		output_fd;
	
	input_fd = STDIN_FILENO;
	output_fd = STDOUT_FILENO;
	
	pipe_token = find_pipe(tokens);
	if (!pipe_token)
	{
		execute_command(tokens, env_list, t_env);
		return ;
	}
	run_pipeline(tokens, t_env, input_fd, output_fd);
}

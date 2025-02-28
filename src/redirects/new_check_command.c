/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_check_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:19:01 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/27 12:30:22 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	save_original_stdout(int *saved)
{
	*saved = dup(STDOUT_FILENO);
	if (*saved == -1)
		perror("minishell: dup");
	return (*saved != -1);
}

static int	apply_redirection(t_token *token)
{
	int		fd;
	char	*filename;

	filename = token->next->value;
	fd = -1;
	if (token->type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token->type == TRUNC)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static void	remove_redirection(t_token **t, t_token *prev, t_token *curr)
{
	t_token *file;
	
	file = curr->next;
	if (prev)
		prev->next = file->next;
	else 
		*t = file->next;
}

static int process_redirections(t_token **tokens)
{
	t_token	*curr;
	t_token *prev;

	prev = NULL;
	curr = *tokens;
	while (curr)
	{
		if (curr->type == TRUNC || curr->type == APPEND)
		{
			if (!apply_redirection(curr))
				return (0);
			remove_redirection(tokens, prev, curr);
			if (prev)
				curr = prev->next;
			else
				curr = *tokens;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (1);
}

static void	restore_original_stdout(int saved)
{
	if (saved != -1)
	{
		dup2(saved, STDOUT_FILENO);
		close(saved);
	}
}

int internal_command(t_token *t, t_env_list *env)
{
	int	saved;
	char **args;
	int status;

	status = 0;
	if (!save_original_stdout(&saved) || !process_redirections(&t))
		return (restore_original_stdout(saved), 1);
	args = get_args(t, count_args(t));
	if (!args)
		return (restore_original_stdout(saved), 1);
	if (builtin(args[0]))
	{
		execute_builtin(args, env);
		restore_original_stdout(saved);
		return (1);
	}
	return (restore_original_stdout(saved), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n2_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:19:01 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/07 15:43:07 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_original_stdin(int *saved)
{
	*saved = dup(STDIN_FILENO);
	if (*saved == -1)
		perror("minishell: dup");
	return (*saved != -1);
}

int	save_original_stdout(int *saved)
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
	t_token	*file;

	file = curr->next;
	if (prev)
		prev->next = file->next;
	else
		*t = file->next;
}

static int	process_redirections(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

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

int redirects(t_token *t, t_env *env)
{
	int status;

	status = 0;
	(void)env;
	if (!process_redirections(&t))
	{
		get_ms()->exit_status = 1;
		return (1);
	}
	return (0);
}

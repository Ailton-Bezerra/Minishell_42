/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n2_check_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:19:01 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/21 19:54:13 by ailbezer         ###   ########.fr       */
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
	if (token->type == APPEND || token->type == TRUNC)
	{
		if (token->type == APPEND)
			handle_output_redirection(filename, 1);
		else if (token->type == TRUNC)
			handle_output_redirection(filename, 0);
	} 
	else if (token->type == INPUT)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(fd);
			return (0);
		}
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
		if (curr->type == TRUNC || curr->type == APPEND || curr->type == INPUT)
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
		int pipe = 0;
		t_token *tmp = get_ms()->tokens;
		while(tmp)
		{
			if (tmp->type == PIPE)
				pipe = 1;
			tmp = tmp->next;
		}
		if (pipe)
			get_ms()->exit_status = 0;
		else
			get_ms()->exit_status = 1;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:47:38 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/23 18:05:35 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*outfile(t_token *token);
static char	*infile(t_token *token);

static t_command	*new_cmd_node(int pipe_out, t_token *tmp_token)
{
	t_command	*new;

	new = gc_malloc(sizeof(t_command));
	new->args = NULL;
	new->path = NULL;
	new->pipe_out = pipe_out;
	new->infile = infile(tmp_token);
	if (new->infile && !ft_strncmp(new->infile, "error", 6))
		new->outfile = NULL;
	new->infile_fd = -1;
	new->outfile_fd = -1;
	new->fd_error = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_command	*last_cmd_node(t_command *head)
{
	if (!head)
		return (NULL);
	while (head && head->next)
		head = head->next;
	return (head);
}

static void	append_cmd(t_command **head, int pipe_out, t_token *tmp_token)
{
	t_command	*new;

	new = new_cmd_node(pipe_out, tmp_token);
	if (!*head)
		*head = new;
	else
	{
		new->prev = last_cmd_node(*head);
		last_cmd_node(*head)->next = new;
	}
}

static char	*infile(t_token *token)
{
	char	*infile;
	
	infile = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == INPUT)
		{
			infile = token->next->value;
			if (open(infile, O_RDONLY) == -1)
			{
				perror("minishell");
				return ("error");
			}
		}
		token = token->next;
	}
	return (infile);
}

static char	*outfile(t_token *token)
{
	char	*outfile;
	
	outfile = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == TRUNC || token->type == APPEND)
		{
			outfile = token->next->value;
			if (token->type == APPEND)
			{
				if (open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644) == -1)
				{
					perror("minishell");
					break ;
				}
			}
			else
			{
				if (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
				{
					perror("minishell");
					break ;
				}
			}
		}
		token = token->next;
	}
	return (outfile);
}

static void	remove_redirection(t_token *prev, t_token *curr)
{
	t_token	*file;
	t_token **t;
	
	t = &get_ms()->tokens;
	file = curr->next;
	if (prev)
		prev->next = file->next;
	else
		*t = file->next;
}

t_command	*creat_cmd_list(t_token *tmp_token)
{
	t_command	*cmd_list;
	int			pipe_out;
	int			cmd_qtd;
	t_token		*init;

	cmd_list = NULL;
	cmd_qtd = count_pipes(get_ms()->tokens) + 1;
	while (tmp_token)
	{
		init = tmp_token;
		pipe_out = (cmd_qtd - 1 > 0);
		append_cmd(&cmd_list, pipe_out, tmp_token);
		while (tmp_token && tmp_token->type != PIPE)
		{
			if (tmp_token->type == APPEND || tmp_token->type == TRUNC)
			{
				last_cmd_node(cmd_list)->outfile_fd = get_outfile_fd(tmp_token, last_cmd_node(cmd_list)->outfile);
				remove_redirection(tmp_token->prev, tmp_token);
			}
			else if (tmp_token->type == INPUT)
			{
				last_cmd_node(cmd_list)->infile_fd = get_infile_fd(tmp_token, last_cmd_node(cmd_list)->infile);
				remove_redirection(tmp_token->prev, tmp_token);
			}
			tmp_token = tmp_token->next;
		}
		last_cmd_node(cmd_list)->args = prepare_command(init);
		last_cmd_node(cmd_list)->path = get_command_path(last_cmd_node(cmd_list)->args[0], get_ms()->env_list->var);
		if (tmp_token)
		{
			tmp_token = tmp_token->next;
			cmd_qtd--;
		}
	}
	// print_tokens(get_ms()->tokens);
	return (cmd_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:47:38 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/24 15:19:51 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_command	*new_cmd_node(int pipe_out, t_token *tmp_token)
{
	t_command	*new;

	(void)tmp_token;
	new = gc_malloc(sizeof(t_command));
	new->args = NULL;
	new->path = NULL;
	new->pipe_out = pipe_out;
	new->infile = NULL;
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
		if (!ft_strncmp(tmp_token->value, "", 1))
		{
			tmp_token = tmp_token->next;
			continue ;
		}
		append_cmd(&cmd_list, pipe_out, tmp_token);
		while (tmp_token && tmp_token->type != PIPE)
		{
			if (tmp_token->type == INPUT)
			{
				last_cmd_node(cmd_list)->infile = infile(tmp_token);
				if (last_cmd_node(cmd_list)->infile && !ft_strncmp(last_cmd_node(cmd_list)->infile, "error", 6))
				{
					last_cmd_node(cmd_list)->infile_fd = -1;
					while (tmp_token && tmp_token->type != PIPE)
					{
						if (tmp_token->type == APPEND || tmp_token->type == TRUNC || tmp_token->type == INPUT)
						remove_redirection(tmp_token->prev, tmp_token);
						tmp_token = tmp_token->next;
					}
					break ;
				}
				last_cmd_node(cmd_list)->infile_fd = get_infile_fd(tmp_token, last_cmd_node(cmd_list)->infile);
				remove_redirection(tmp_token->prev, tmp_token);
			}
			else if (tmp_token->type == APPEND || tmp_token->type == TRUNC)
			{
				last_cmd_node(cmd_list)->outfile = outfile(tmp_token);
				if (last_cmd_node(cmd_list)->outfile && !ft_strncmp(last_cmd_node(cmd_list)->outfile, "error", 6))
				{
					last_cmd_node(cmd_list)->outfile_fd = -1;
					while (tmp_token && tmp_token->type != PIPE)
					{
						if (tmp_token->type == APPEND || tmp_token->type == TRUNC || tmp_token->type == INPUT)
						remove_redirection(tmp_token->prev, tmp_token);
						tmp_token = tmp_token->next;
					}
					break ;
				}
				last_cmd_node(cmd_list)->outfile_fd = get_outfile_fd(tmp_token, last_cmd_node(cmd_list)->outfile); 
				remove_redirection(tmp_token->prev, tmp_token);
			}
			if (tmp_token)
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

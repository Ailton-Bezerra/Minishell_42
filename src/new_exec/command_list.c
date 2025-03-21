/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:47:38 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/21 14:20:39 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*new_cmd_node(char **args, int pipe_in, int pipe_out)
{
	t_command	*new;

	new = gc_malloc(sizeof(t_command));
	new->args = args;
	// if (builtin(args[0]))
	// 	new->path = "builtin";
	// else
	new->path = get_command_path(args[0], get_ms()->env_list->var);
	new->pipe_in = pipe_in;
	new->pipe_out = pipe_out;
	new->next = NULL;
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

void	append_cmd(char **args, t_command **head, int pipe_in, int pipe_out)
{
	t_command	*new;

	new = new_cmd_node(args, pipe_in, pipe_out);
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
	char		**args;
	int			pipe_in;
	int			pipe_out;
	int			cmd_qtd;

	pipe_in = 0;
	cmd_list = NULL;
	cmd_qtd = count_pipes(get_ms()->tokens) + 1;
	while (tmp_token)
	{
		pipe_out = (cmd_qtd - 1 > 0);
		args = prepare_command(tmp_token);
		append_cmd(args, &cmd_list, pipe_in, pipe_out);
		pipe_in++;
		while (tmp_token && tmp_token->type != PIPE)
			tmp_token = tmp_token->next;
		if (tmp_token)
		{
			tmp_token = tmp_token->next;
			cmd_qtd--;
		}
	}
	return (cmd_list);
}

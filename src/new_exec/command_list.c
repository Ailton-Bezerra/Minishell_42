/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:07:57 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/19 12:50:32 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*new_cmd_node(char **args, int pipe_in, int pipe_out)
{
	t_command	*new;

	new = gc_malloc(sizeof(t_command));
	new->args = args;
	if (builtin(args[0]))
		new->path = "builtin";
	else
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
		last_cmd_node(*head)->next = new;
}

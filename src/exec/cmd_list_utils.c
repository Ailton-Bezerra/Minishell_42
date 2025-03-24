/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:14:26 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/24 18:42:34 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*new_cmd_node(int pipe_out, t_token *tmp_token)
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

void	append_cmd(t_command **head, int pipe_out, t_token *tmp_token)
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

int new_cmd(t_token **tmp, t_command **cmd_list, int pipe_out)
{
	if (!ft_strncmp((*tmp)->value, "", 1))
	{
		(*tmp) = (*tmp)->next;
		return (0);
	}
	append_cmd(cmd_list, pipe_out, *tmp);
	return (1);
}

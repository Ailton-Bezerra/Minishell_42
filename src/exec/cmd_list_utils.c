/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:14:26 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/25 19:03:08 by ailbezer         ###   ########.fr       */
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

int	new_cmd(t_token **tmp, t_command **cmd_list, int pipe_out)
{
	if (!ft_strncmp((*tmp)->value, "", 1))
	{
		(*tmp) = (*tmp)->next;
		return (0);
	}
	append_cmd(cmd_list, pipe_out, *tmp);
	return (1);
}

int	set_heredoc(t_command *last, t_token **tmp, int *cmd_index)
{
	t_hd_list	**arr_hds;

	arr_hds = get_ms()->hd->arr_hds;
	last->infile = last_hd_node(get_ms()->hd->arr_hds[*cmd_index])->filename;
	if (last->infile && !ft_strncmp(last->infile, "error", 6))
	{
		last->infile_fd = -1;
		while (*tmp && (*tmp)->type != PIPE)
		{
			if ((*tmp)->type == APPEND
				|| (*tmp)->type == APPEND
				|| (*tmp)->type == TRUNC || (*tmp)->type == INPUT)
				remove_redirection((*tmp)->prev, *tmp);
			*tmp = (*tmp)->next;
		}
		return (0);
	}
	last->infile_fd = open(last->infile, O_RDONLY);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:47:38 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/24 19:31:10 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_input(t_command *last, t_token **tmp)
{
	last->infile = infile(*tmp);
	if (last->infile && !ft_strncmp(last->infile, "error", 6))
	{
		last->infile_fd = -1;
		while (*tmp && (*tmp)->type != PIPE)
		{
			if ((*tmp)->type == APPEND
				|| (*tmp)->type == TRUNC || (*tmp)->type == INPUT)
			remove_redirection((*tmp)->prev, *tmp);
			*tmp = (*tmp)->next;
		}
		return (0) ;
	}
	last->infile_fd = get_infile_fd(*tmp, last->infile);
	return (1);
}

static int	set_output(t_command *last, t_token **tmp)
{
	last->outfile = outfile(*tmp);
	if (last->outfile && !ft_strncmp(last->outfile, "error", 6))
	{
		last->outfile_fd = -1;
		while (*tmp && (*tmp)->type != PIPE)
		{
			if ((*tmp)->type == APPEND
				|| (*tmp)->type == TRUNC || (*tmp)->type == INPUT)
			remove_redirection((*tmp)->prev, *tmp);
			*tmp = (*tmp)->next;
		}
		return (0);
	}
	last->outfile_fd = get_outfile_fd(*tmp, last->outfile);
	return (1);
}

static int handle_redirects(t_token **tmp, t_command *cmd_list)
{
	t_command	*last;
	
	last = last_cmd_node(cmd_list);
	if ((*tmp)->type == INPUT)
	{
		if (!set_input(last, tmp))
			return (0);
	}
	else if ((*tmp)->type == APPEND || (*tmp)->type == TRUNC)
	{
		if (!set_output(last, tmp))
			return (0);
	}
	return (1);
}

static void process_cmd(t_token **tmp, t_command *cmd_list)
{
	while (*tmp && (*tmp)->type != PIPE)
	{
		if ((*tmp)->type == INPUT
			|| (*tmp)->type == APPEND || (*tmp)->type == TRUNC)
		{
			if (!handle_redirects(tmp, cmd_list))
				break ;
			remove_redirection((*tmp)->prev, *tmp);
		}
		if (*tmp)
			*tmp = (*tmp)->next;
	}
}

t_command	*creat_cmd_list(t_token *tmp)
{
	t_command	*cmd_list;
	int			pipe_out;
	int			cmd_qtd;
	t_token		*init;
	t_command   *last;

	cmd_list = NULL;
	cmd_qtd = count_pipes(get_ms()->tokens) + 1;
	while (tmp)
	{
		init = tmp;
		pipe_out = (cmd_qtd-- - 1 > 0);
		if(!new_cmd(&tmp, &cmd_list, pipe_out))
			continue ;
		process_cmd(&tmp, cmd_list);
		last = last_cmd_node(cmd_list);
		last->args = prepare_command(init);
		last->path = get_command_path(last->args[0], get_ms()->env_list->var);
		if (tmp)
			tmp = tmp->next;
	}
	// print_tokens(get_ms()->tokens);
	return (cmd_list);
}

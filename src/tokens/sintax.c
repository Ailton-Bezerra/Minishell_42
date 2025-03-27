/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:49:27 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/27 17:27:55 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redirect(enum e_token type, t_token *next)
{
	if (((type == APPEND && next && next->type != WORD))
		|| (type == APPEND && !next))
		return (printf("syntax error near unexpected token `>>'\n"), 0);
	else if ((type == TRUNC && next && next->type != WORD)
		|| (type == TRUNC && !next))
		return (printf("syntax error near unexpected token `>'\n"), 0);
	else if (((type == HERE_DOC && next && next->type != WORD))
		|| (type == HERE_DOC && !next))
		return (printf("syntax error near unexpected token `<<'\n"), 0);
	else if (((type == INPUT && next && next->type != WORD))
		|| (type == INPUT && !next))
		return (printf("syntax error near unexpected token `<'\n"), 0);
	return (1);
}

static int	check_pipe(t_token *tmp)
{
	if ((tmp->type == PIPE && !tmp->prev) || (tmp->type == PIPE && !tmp->next))
		return (printf("syntax error near unexpected token `|'\n"), 0);
	return (1);
}

int	check_sintax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (!check_redirect(tmp->type, tmp->next) || !check_pipe(tmp))
		{
			get_ms()->exit_status = 2;
			return (0);
		}
		if ((ft_strchr(tmp->value, '$') && !tmp->prev)
			|| (ft_strchr(tmp->value, '$') && tmp->prev
				&& tmp->prev->type != HERE_DOC))
			tmp->value = handle_expansion(tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

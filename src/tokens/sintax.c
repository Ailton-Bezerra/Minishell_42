/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:49:27 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/19 15:10:52 by ailbezer         ###   ########.fr       */
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

static int	check_pipe(enum e_token type, t_token *next, t_token *first)
{
	if ((((type == PIPE && next && next->type != WORD))
			|| (type == PIPE && !next)) || first->type == PIPE)
		return (printf("syntax error near unexpected token `|'\n"), 0);
	return (1);
}

int	chek_sintax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (!check_redirect(tmp->type, tmp->next))
			return (0);
		else if (!check_pipe(tmp->type, tmp->next, tokens))
			return (0);
		if (ft_strchr(tmp->value, '$'))
			tmp->value = handle_expansion(tmp->value);
		tmp->value = remove_outer_quotes(tmp->value, 0, 0);
		tmp = tmp->next;
	}
	return (1);
}

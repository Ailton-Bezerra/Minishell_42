/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:49:27 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/07 16:55:47 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int chek_sintax(t_token *tokens)
{
	t_token *tmp;
	t_token *first;

	first = tokens;
	tmp = tokens;
	while (tmp)
	{
		if (((tmp->type == APPEND && tmp->next && tmp->next->type != WORD))
			|| (tmp->type == APPEND && !tmp->next))
			return (printf("syntax error near unexpected token `>>'\n"));
		else if ((tmp->type == TRUNC && tmp->next
				&& tmp->next->type != WORD) 
				|| (tmp->type == TRUNC && !tmp->next))
			return (printf("syntax error near unexpected token `>'\n"));
		else if ((((tmp->type == PIPE && tmp->next && tmp->next->next != WORD))
				|| (tmp->type == PIPE && !tmp->next)) || first->type == PIPE)
			return (printf("syntax error near unexpected token `|'\n"));
		else if (((tmp->type == HERE_DOC && tmp->next
				&& tmp->next->next != WORD))
				|| (tmp->type == HERE_DOC && !tmp->next))
			return(printf("syntax error near unexpected token `<<'\n"));
		else if (((tmp->type == INPUT && tmp->next && tmp->next->type != WORD))
				|| (tmp->type == INPUT && !tmp->next))
			return (printf("syntax error near unexpected token `<'\n"));
		tmp = tmp->next;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:03:48 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/27 16:52:51 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_quotes(t_token *t, int *i, int *j, char **final_str)
{
	char	quote;
	char	*tmp;

	tmp = ft_strdup(t->value + *i);
	if (ft_strchr(t->value + *i, '\'') || ft_strchr(t->value + *i, '\"'))
	{
		while (t->value[*i] && !ft_strchr("\'\"", t->value[*i]))
		{
			*final_str = ft_strjoin(*final_str, (char []){t->value[*i], '\0'});
			(*i)++;
		}
		quote = *ft_strchr("\'\"", t->value[*i]);
		*j = *i + 1;
		while (t->value[*j] == quote)
			(*j)++;
		while (t->value[*j] && t->value[*j] != quote)
		{
			*final_str = ft_strjoin(*final_str, (char []){t->value[*j], '\0'});
			(*j)++;
		}
		tmp = t->value + *i;
		*i = *j;
	}
}

void	clear_quotes(t_token *t)
{
	int		i;
	char	*final_str;
	int		j;

	while (t)
	{
		if (t->prev && t->prev->type == HERE_DOC)
		{
			t = t->next;
			continue ;
		}
		final_str = ft_strdup("");
		i = 0;
		while (t->value[i])
		{
			remove_quotes(t, &i, &j, &final_str);
			if (t->value[i])
				i++;
		}
		if (ft_strchr(t->value, '\'') || ft_strchr(t->value, '\"'))
			t->value = final_str;
		t = t->next;
	}	
}

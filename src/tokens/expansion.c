/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:55:11 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/08 17:12:37 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*change_to_value(const char *input, int *var_len)
{
	int		end_var;
	char	*var;
	char	*var_value;

	end_var = 1;
	while (input[end_var]
		&& (ft_isalnum(input[end_var]) || input[end_var] == '_'))
		end_var++;
	if (end_var == 1)
	{
		*var_len = 0;
		return (NULL);
	}
	var = ft_substr(input, 1, end_var - 1);
	var_value = getenv(var);
	if (!var_value)
		var_value = "";
	free(var);
	*var_len = end_var;
	return (var_value);
}

static char	*expand(char *input, char *var_value, int i, int var_len)
{
	char	*start;
	char	*end;
	char	*new_input;

	start = ft_substr(input, 0, i);
	end = ft_strdup(input + i + var_len);
	free(input);
	new_input = ft_strjoin(start, var_value);
	free(start);
	new_input = ft_strjoin_free(new_input, end);
	return (new_input);
}

static void	change_qflags(int *quote, int *double_quote, int *i, char *input)
{
	if (input[*i] == '\'' && !*double_quote)
	{
		*quote = !*quote;
		(*i)++;
	}
	else if (input[*i] == '\"' && !*quote)
	{
		*double_quote = !*double_quote;
		(*i)++;
	}
}

static void	ex_init(t_expand *ex)
{
	ex->quote = 0;
	ex->double_quote = 0;
	ex->index = 0;
}

char	*handle_expansion(char *input)
{
	t_expand	ex;

	ex_init(&ex);
	while (input[ex.index])
	{
		if (input[ex.index] == '\'' && !ex.double_quote)
			change_qflags(&ex.quote, &ex.double_quote, &ex.index, input);
		else if (input[ex.index] == '\"' && !ex.quote)
			change_qflags(&ex.quote, &ex.double_quote, &ex.index, input);
		else if (input[ex.index] == '$' && !ex.quote)
		{
			ex.var_value = change_to_value(input + ex.index, &ex.var_len);
			if (ex.var_len == 0)
			{
				ex.index++;
				continue ;
			}
			input = expand(input, ex.var_value, ex.index, ex.var_len);
			ex.index += ft_strlen(ex.var_value);
		}
		else
			ex.index++;
	}
	return (input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:55:11 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/19 10:38:40 by ailbezer         ###   ########.fr       */
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
	*var_len = end_var;
	return (var_value);
}

static void	ex_init(t_expand *ex)
{
	ex->quote = 0;
	ex->double_quote = 0;
	ex->index = 0;
}

static void	change_quote_flag(char *result, t_expand *ex, int *i)
{
	if (result[*i] == '\'' && !ex->double_quote)
	{
		ex->quote = !ex->quote;
		(*i)++;
	}
	else if (result[*i] == '\"' && !ex->quote)
	{
		ex->double_quote = !ex->double_quote;
		(*i)++;
	}
}

static char	*expand_variable(char *result, t_expand *ex)
{
	char	*new_str;
	size_t	new_len;

	ex->var_value = change_to_value(result + ex->index, &ex->var_len);
	if (ex->var_len > 0)
	{
		new_len = ft_strlen(result) - ex->var_len + ft_strlen(ex->var_value);
		new_str = gc_malloc(new_len + 1);
		ft_strlcpy(new_str, result, ex->index + 1);
		ft_strlcat(new_str, ex->var_value, new_len + 1);
		ft_strlcat(new_str, result + ex->index + ex->var_len, new_len + 1);
		gc_dealocate(result);
		ex->index += ft_strlen(ex->var_value);
		return (new_str);
	}
	else
	{
		ex->index++;
		return (result);
	}
}

char	*handle_expansion(char *input)
{
    t_expand	ex;

    ex_init(&ex);
    while (input[ex.index])
    {
        if ((input[ex.index] == '\'' && !ex.double_quote) || (input[ex.index] == '\"' && !ex.quote))
            change_quote_flag(input, &ex, &ex.index);
        else if (input[ex.index] == '$' && !ex.quote)
            input = expand_variable(input, &ex);
        else
            ex.index++;
    }
	return (input);
}

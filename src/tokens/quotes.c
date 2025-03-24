/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:31:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/24 15:02:11 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;

	new = gc_malloc(n + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, n);
	new[n] = '\0';
	return (new);
}

static char	*parse_quotes(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
	{
		printf("Error: unclosed quotes\n");
		return (NULL);
	}
	return (line);
}

char	*remove_outer_quotes(char *input, int single_q, int double_q)
{
	char	*result;
	int		i;
	int		j;

	result = gc_malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < (int)ft_strlen(input))
	{
		if ((input[i] == '\'' && !double_q) || (input[i] == '"' && !single_q))
		{
			if (input[i] == '\'')
				single_q = !single_q;
			else
				double_q = !double_q;
		}
		else
			result[j++] = input[i];
	}
	result[j] = '\0';
	return (result);
}

t_token	*handle_quotes(char *line, t_token *tokens)
{
	int		i;

	if (!parse_quotes(line))
		return (NULL);
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		process_token(&tokens, line, &i);
	}
	return (tokens);
}

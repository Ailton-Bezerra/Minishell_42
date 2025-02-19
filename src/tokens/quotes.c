/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:31:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/19 10:48:19 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_token(t_token **tokens, char *line, int *i)
{
    char	*final_str;
    char	quote;
    char	*temp_str;
    int		start;
	
    final_str = ft_strdup("");
	quote = 0;
    while (line[*i] && !ft_strchr(" \t\n", line[*i]))
    {
        if (line[*i] == '\'' || line[*i] == '\"')
        {
            quote = line[*i];
            start = *i;
            (*i)++;
            while (line[*i] && line[*i] != quote)
                (*i)++;
            temp_str = ft_substr(line, start, *i - start);
            final_str = ft_strjoin(final_str, temp_str);
            // if (line[*i] == quote)
            (*i)++;
        }
        else
        {
            temp_str = ft_substr(line, *i, 1);
            final_str = ft_strjoin(final_str, temp_str);
            (*i)++;
        }
    }
    add_token(tokens, final_str/*, quote*/);
}

/**
 * @brief   Checks for unclosed single or double quotes in a string.
 * 
 * @param   line  The input string to be analyzed.
 * 
 * @return  Returns "OK" if all quotes are properly closed.
 *			returns NULL & error message if there are unclosed quotes.
 */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:31:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/11 18:26:29 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;

	new = malloc(n + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, n);
	new[n] = '\0';
	return (new);
}

static void	add_token_from_line(t_token **tokens, char *line, int start,
	int end)
{
	char	*token_str;

	token_str = ft_strndup(&line[start], end - start);
	add_token(tokens, token_str);
	free(token_str);
}

/**
 * @brief   Processes a token from the input line and adds it to the token list.
 * 
 * @param   tokens  Pointer to the list of tokens.
 * @param   line    The input string being tokenized.
 * @param   i       Pointer to the current index in the input string.
 * 
 * @return  None. The function updates the token list by extracting tokens 
 *          based on spaces and quotes.
 */
static void	process_token(t_token **tokens, char *line, int *i)
{
	int		start;
	char	quote;

	start = *i;
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[(*i)++];
		start = *i;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		add_token_from_line(tokens, line, start, *i);
		(*i)++;
	}
	else
	{
		while (line[*i] && line[*i] != ' ' && line[*i] != '\''
			&& line[*i] != '\"')
			(*i)++;
		add_token_from_line(tokens, line, start, *i);
	}
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
	return ("OK");
}

t_token	*handle_quotes(char *line, t_token *tokens)
{
	int		i;

	if (!parse_quotes(line))
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		process_token(&tokens, line, &i);
	}
	free(line);
	return (tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:31:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/06 11:32:53 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int	parse_quotes(const char *line, t_token *tokens)
{
	char	quote;
	int		i;
	int		start;
	int		single_quote;
	int		double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		start = i;
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i++];
			start = i;
			while (line[i] && line[i] != quote)
				i++;
			add_token(&tokens, ft_strdup(&line[start]));
			i++;
		}
		else
		{
			while (line[i] && line[i] != ' ' && line[i] != '\''
				&& line[i] != '\"')
				i++;
			add_token(&tokens, ft_strdup(&line[start]));
		}
	}
	if (single_quote || double_quote)
	{
		printf("Error: unclosed quotes\n");
		return (0);
	}
	return (1);
}*/

// t_token	*split_tokens(const char *input)
// {
// 	t_token	*tokens_head;
// 	int		i;

// 	tokens_head = NULL;
// 	i = 0;
// 	while (input[i])
// 	{
// 		while (input[i] == ' ')
// 			i++;
// 		if (!input[i])
// 			break ; 
// 		if (!parse_quotes(&input[i], tokens_head))
// 		{
// 			free_tokens(tokens_head);
// 			return (NULL);
// 		}
		
// 		{
// 			add_token(&tokens_head, token);
// 			free(token);
// 		}
// 	}
// 	return (tokens_head);
// }

static char	*ft_strndup(const char *s, size_t n)
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

t_token	*tokenize(char *line, t_token *tokens)
{
	int		i;

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

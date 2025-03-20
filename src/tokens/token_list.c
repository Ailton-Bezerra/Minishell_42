/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:17:00 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/20 14:44:13 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token_node(char *content)
{
	t_token	*new_node;

	new_node = gc_malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(content);
	new_node->type = define_types(new_node->value);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_token(t_token **head, char *content)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = new_token_node(content);
	if (!new_node)
		return ;
	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		new_node->prev = temp;
		temp->next = new_node;
	}
}

static void	append_char(char **final_str, char *line, int *i)
{
	char	*temp_str;

	temp_str = ft_substr(line, *i, 1);
	*final_str = ft_strjoin(*final_str, temp_str);
	(*i)++;
}

static void	process_quote(char *line, int *i, char **final_str, char quote)
{
	char	*temp_str;
	int		start;

	temp_str = ft_substr(line, *i, 1);
	*final_str = ft_strjoin(*final_str, temp_str);
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	temp_str = ft_substr(line, start, *i - start);
	*final_str = ft_strjoin(*final_str, temp_str);
	if (line[*i] == quote)
	{
		temp_str = ft_substr(line, *i, 1);
		*final_str = ft_strjoin(*final_str, temp_str);
		(*i)++;
	}
}

void	process_token(t_token **tokens, char *line, int *i)
{
	char	*final_str;
	char	quote;

	final_str = ft_strdup("");
	while (line[*i] && !ft_strchr(" \t\n", line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			process_quote(line, i, &final_str, quote);
		}
		else
			append_char(&final_str, line, i);
	}
	add_token(tokens, final_str);
}

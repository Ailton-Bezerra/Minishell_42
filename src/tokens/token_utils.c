/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:34:36 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/06 12:03:25 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// lembrar de liberar a memoria alocada depois;
static t_token	*new_token_node(char *content)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(content);
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
		temp->next = new_node;
	}
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: [%s]\n", tokens->value);
		tokens = tokens->next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

/**
 * @brief Tokenizes the input string into a linked list of words split by spaces.
 * @param input The input string to be tokenized (must not be NULL).
 * @return A pointer to the head of the linked list containing tokens,
 * or NULL if empty.
 */
// t_token	*tokenizer_input(const char *input)
// {
// 	t_token	*tokens_head;
// 	char	**tokens_split;
// 	int		i;

// 	i = 0;
// 	tokens_head = NULL;
// 	tokens_split = ft_split(input, ' ');
// 	while (tokens_split[i])
// 	{
// 		add_token(&tokens_head, tokens_split[i]);
// 		free(tokens_split[i++]);
// 	}
// 	free(tokens_split);
// 	return (tokens_head);
// }

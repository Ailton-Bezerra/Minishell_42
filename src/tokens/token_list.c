/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:17:00 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/06 15:35:08 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token_node(char *content)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(content);
	new_node->type = define_types(new_node->value);
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

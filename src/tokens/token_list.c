/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:17:00 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/19 10:50:52 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token_node(char *content /*, char quote*/)
{
	t_token	*new_node;
	// char	*new_value;
	
	new_node = gc_malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	// if (quote == '\'')
	// {
	// 	new_value = strdup("\'");
	// 	new_value = ft_strjoin(new_value, ft_strdup(content));
	// 	new_value = ft_strjoin(new_value, ft_strdup("\'"));
	// 	new_node->value = new_value;
	// }
	// else if (quote == '\"')
	// {
	// 	new_value = strdup("\"");
	// 	new_value = ft_strjoin(new_value, ft_strdup(content));
	// 	new_value = ft_strjoin(new_value, ft_strdup("\""));
	// 	new_node->value = new_value;
	// }
	// else
	new_node->value = ft_strdup(content);
	new_node->type = define_types(new_node->value);
	new_node->next = NULL;
	return (new_node);
}

void	add_token(t_token **head, char *content/*, char quote*/)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = new_token_node(content/*, quote*/);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:39:21 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/17 14:39:21 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/garbage_collector.h"

t_garbage_node	**get_garbage_list(void)
{
	static t_garbage_node	*garbage_list;

	return (&garbage_list);
}

void	init_garbage_collector(void)
{
	t_garbage_node	**garbage_list;

	garbage_list = get_garbage_list();
	*garbage_list = NULL;
}

void	*gc_malloc(size_t size)
{
	void			*ptr;
	t_garbage_node	*new_node;
	t_garbage_node	**garbage_list;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	garbage_list = get_garbage_list();
	new_node->ptr = ptr;
	new_node->next = *garbage_list;
	*garbage_list = new_node;
	return (ptr);
}

t_garbage_node	*gc_dealocate_node(t_garbage_node **garbage_list, void *ptr)
{
	t_garbage_node	*prev;
	t_garbage_node	*cur;

	prev = NULL;
	cur = *garbage_list;
	while (cur)
	{
		if (cur->ptr == ptr)
		{
			if (prev)
				prev->next = cur->next;
			else
				*garbage_list = cur->next;
			return (cur);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

int	gc_dealocate(void *ptr)
{
	t_garbage_node	**garbage_list;
	t_garbage_node	*node_to_free;

	if (!ptr)
		return (0);
	garbage_list = get_garbage_list();
	node_to_free = gc_dealocate_node(garbage_list, ptr);
	if (node_to_free)
	{
		if (node_to_free->ptr)
			free(node_to_free->ptr);
		node_to_free->ptr = NULL;
		free(node_to_free);
		return (1);
	}
	return (0);
}

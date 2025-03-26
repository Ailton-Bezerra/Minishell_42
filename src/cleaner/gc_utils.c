/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:38:31 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/17 14:38:31 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/garbage_collector.h"

void	gc_cleanup(void)
{
	t_garbage_node	**garbage_list;
	t_garbage_node	*cur;
	t_garbage_node	*tmp;

	cur = NULL;
	tmp = NULL;
	garbage_list = get_garbage_list();
	cur = *garbage_list;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->ptr)
		{
			free(tmp->ptr);
			tmp->ptr = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	*garbage_list = NULL;
}

int	gc_track(void *ptr)
{
	t_garbage_node	*new_node;
	t_garbage_node	**garbage_list;

	if (!ptr)
		return (0);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (0);
	garbage_list = get_garbage_list();
	new_node->ptr = ptr;
	new_node->next = *garbage_list;
	*garbage_list = new_node;
	return (1);
}

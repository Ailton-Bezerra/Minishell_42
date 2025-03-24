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

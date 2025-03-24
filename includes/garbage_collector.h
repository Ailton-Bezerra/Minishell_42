/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:38:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/17 14:38:40 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>

typedef struct s_garbage_node
{
	void					*ptr;
	struct s_garbage_node	*next;
}							t_garbage_node;

t_garbage_node	**get_garbage_list(void);
void			init_garbage_collector(void);
void			*gc_malloc(size_t size);
t_garbage_node	*gc_dealocate_node(t_garbage_node **garbage_list, void *ptr);
int				gc_dealocate(void *ptr);
void			gc_cleanup(void);
int				gc_track(void *ptr);

#endif
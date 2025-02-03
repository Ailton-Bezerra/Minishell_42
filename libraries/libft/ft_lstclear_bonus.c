/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:56:38 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/23 15:23:18 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

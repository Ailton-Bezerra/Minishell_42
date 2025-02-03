/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:29:50 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/10 14:58:19 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*m;
	size_t			i;

	m = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (m[i] == (unsigned char)c)
			return (m + i);
		i++;
	}
	return (NULL);
}

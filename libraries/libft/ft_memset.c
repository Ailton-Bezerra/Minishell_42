/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:22:32 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/09 11:05:57 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*m;

	i = 0;
	m = (char *)s;
	while (i < n)
	{
		m[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:04:12 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/09 14:47:42 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if ((dest == NULL && src == NULL) && n > 0)
		return (NULL);
	i = -1;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d < s || d >= (s + n))
	{
		while (++i < n)
			d[i] = s[i];
	}
	else
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:35:46 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/09 11:56:40 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	size_t			destl;
	size_t			srcl;

	i = 0;
	destl = 0;
	srcl = 0;
	while (destl < size && dest[destl] != '\0')
		destl++;
	while (src[srcl] != '\0')
		srcl++;
	if (size <= destl)
		return (destl + srcl);
	while (i < (size - destl - 1) && src[i] != '\0')
	{
		dest[destl + i] = src[i];
		i++;
	}
	dest[destl + i] = '\0';
	return (destl + srcl);
}

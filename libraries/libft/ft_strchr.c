/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:10:03 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/22 14:12:02 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	nc;

	i = 0;
	nc = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == nc)
			return ((char *)(s + i));
		i++;
	}
	if (nc == '\0')
		return ((char *)(s + ft_strlen(s)));
	return (NULL);
}

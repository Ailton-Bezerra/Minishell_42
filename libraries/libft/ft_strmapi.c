/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:47:26 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/20 10:41:42 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ns;
	unsigned int	i;

	ns = (char *)gc_malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ns == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		ns[i] = (*f)(i, s[i]);
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

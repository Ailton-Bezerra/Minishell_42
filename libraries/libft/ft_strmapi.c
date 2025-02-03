/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:47:26 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/15 12:34:14 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ns;
	unsigned int	i;

	ns = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
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

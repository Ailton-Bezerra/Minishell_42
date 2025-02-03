/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:16:16 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/14 15:10:07 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*r;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (r == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		r[i + j] = s2[j];
		j++;
	}
	r[i + j] = '\0';
	return (r);
}

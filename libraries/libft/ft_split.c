/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:16:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/23 15:27:18 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_scount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*ft_memsst(char const *s, size_t i, size_t j)
{
	char	*sst;
	size_t	n;

	sst = (char *)malloc(sizeof(char) * (i - j + 1));
	if (sst == NULL)
		return (NULL);
	n = 0;
	while (j < i)
	{
		sst[n] = s[j];
		n++;
		j++;
	}
	sst[n] = '\0';
	return (sst);
}

char	**ft_split(char const *s, char c)
{
	char	**memalloc;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	memalloc = (char **)malloc(sizeof(char *) * (ft_scount(s, c) + 1));
	if (memalloc == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > j)
		{
			memalloc[k] = ft_memsst(s, i, j);
			k++;
		}
	}
	memalloc[k] = NULL;
	return (memalloc);
}

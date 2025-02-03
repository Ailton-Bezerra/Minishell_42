/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:17:10 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/10/25 16:52:49 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(long num)
{
	unsigned int	count;

	count = 0;
	if (num <= 0)
	{
		num = num * -1;
		count++;
	}
	while (num != 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static char	*memalloc(int length)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (length + 1));
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	return (str);
}

static char	*ft_nbr(long num)
{
	int		i;
	int		length;
	char	*str;

	length = ft_len(num);
	str = memalloc(length);
	if (str == NULL)
		return (NULL);
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
	}
	i = length - 1;
	while (num > 0)
	{
		str[i--] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	num;
	char	*str;

	num = n;
	str = ft_nbr(num);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:27:38 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/27 10:34:51 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_exit_status(char *token)
{
	char		*exit;
	char		*new_tkn;
	char		*pos;

	if (!token)
		return (NULL);
	exit = ft_itoa(get_ms()->exit_status);
	if (!exit)
		return (token);
	pos = ft_strnstr(token, "$?", ft_strlen(token));
	while (pos)
	{
		new_tkn = ft_calloc((pos - token) + ft_strlen(exit)
				+ ft_strlen(pos + 2) + 1, sizeof(char));
		if (!new_tkn)
			break ;
		ft_strlcpy(new_tkn, token, pos - token + 1);
		ft_strlcat(new_tkn, exit, ft_strlen(new_tkn) + ft_strlen(exit) + 1);
		ft_strlcat(new_tkn, pos + 2, ft_strlen(new_tkn)
			+ ft_strlen(pos + 2) + 1);
		pos = ft_strnstr(new_tkn, "$?", ft_strlen(new_tkn));
	}
	return (new_tkn);
}

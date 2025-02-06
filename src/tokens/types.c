/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:45:47 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/06 15:33:04 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

enum e_token	define_types(char *type)
{
	if (!ft_strncmp(type, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(type, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(type, ">", 1))
		return (TRUNC);
	else if (!ft_strncmp(type, "<<", 2))
		return (HERE_DOC);
	else if (!ft_strncmp(type, "<", 1))
		return (INPUT);
	else
		return (WORD);
}

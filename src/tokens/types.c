/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:45:47 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/25 18:40:57 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_type(t_token *tokens)
{
	t_token	*temp;
	int		command;

	command = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == WORD && !command && temp->value[0] != '\0')
		{
			temp->type = COMMAND;
			command = 1;
		}
		else if (temp->type == PIPE && temp->next && temp->next->type == WORD
			&& temp->next->value[0] != '\0')
			temp->next->type = COMMAND;
		else if (temp->type == PIPE && temp->next && temp->next->next
			&& temp->next->type == WORD && temp->next->value[0] == '\0')
			temp->next->next->type = COMMAND;
		temp = temp->next;
	}
}

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

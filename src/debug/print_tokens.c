/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:08:56 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/20 12:04:16 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_type(enum e_token type)
{
	static char	*ctype[9] = {"WORD", "PIPE",
		"APPEND", "TRUNC",
		"INPUT", "HERE_DOC", "COMMAND",
		"OPTION", "FD"};

	return (ft_strdup(ctype[type]));
}

void	print_tokens(t_token *token)
{
	t_token	*temp;
	char	*type;
	int		i;

	temp = token;
	i = 0;
	printf("\001\033[1;32m\002========================="END"\n");
	while (temp)
	{	
		printf("token[%d] value: %s\n", i, temp->value);
		type = get_type(temp->type);
		printf("token[%d] type : %s\n", i++, type);
		temp = temp->next;
		printf("\001\033[1;32m\002========================="END"\n");
	}
}

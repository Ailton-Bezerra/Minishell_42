/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:08:56 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/06 15:18:35 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_type(enum e_token type)
{
	static char	*ctype[6] = {"WORD", "PIPE",
		"APPEND", "TRUNC",
		"INPUT", "HERE_DOC"};

	return (ft_strdup(ctype[type]));
}

void	print_tokens(t_token *token)
{
	t_token	*temp;
	char	*type;
	int		i;

	temp = token;
	i = 0;
	printf("\n\033[32m=========================\n\33[0m");
	while (temp)
	{	
		printf("token[%d] value: %s\n", i, temp->value);
		type = get_type(temp->type);
		printf("token[%d] type : %s\n", i++, type);
		free(type);
		temp = temp->next;
		printf("\033[32m=========================\n\33[0m");
	}
}

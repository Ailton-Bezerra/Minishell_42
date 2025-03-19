/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:08:56 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/19 12:33:14 by cabo-ram         ###   ########.fr       */
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

// void print_hdlist(void)
// {
// 	t_hd_list *temp;

// 	temp = get_ms()
	
// }

void	print_cmd_list(t_command *cmd_list)
{
	t_command	*temp;
	int		i;
	int		j;

	temp = cmd_list;
	i = 0;
	printf("\001\033[1;32m\002========================="END"\n");
	while (temp)
	{	
		j = 0;
		while(temp->args[j])
		{
			printf("cmd[%d] arg[%d] : %s\n", i, j, temp->args[j]);
			j++;
		}
		printf("cmd[%d] path: %s\n", i, temp->path);
		printf("cmd[%d] pipe_in: %d\n", i, temp->pipe_in);
		printf("cmd[%d] pipe_out: %d\n", i++, temp->pipe_out);
		temp = temp->next;
		printf("\001\033[1;32m\002========================="END"\n");
	}
}

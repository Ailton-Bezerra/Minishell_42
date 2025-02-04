/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/04 17:05:04 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*read_input(void)
{
	char	*input;

	input = readline("MINISHEL > ");
	if (!input)
	{
		printf("exiting\n");
		rl_clear_history();
		exit(-42);
	}
	if (*input)
		add_history(input);
	// printf("%s\n", input);
	// rl_clear_history();
	return (input);
}

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = read_input();
		tokens = tokenizer_input(input);
		// t_token *temp = tokens;
		// int i = 0;
		// while(temp)
		// {	
		// 	printf("-----------------------------\n");
		// 	printf("token [%d]: %s\n", i++, temp->value);
		// 	temp = temp->next;
		// }
		free(input);
		free_tokens(tokens);
	}
	rl_clear_history();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/07 16:25:19 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*read_input(void)
{
	char	*input;

	input = readline(YELLOW "MINISHELL > " END);
	if (!input)
	{
		printf("exiting\n");
		return (NULL);
	}
	if (*input && input)
		add_history(input);
	return (input);
}

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		tokens = tokenizer(input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		free(input);
		print_tokens(tokens);
		free_tokens(tokens);
	}
	rl_clear_history();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/08 15:48:04 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_input(char **input)
{
	*input = readline(YELLOW "MINISHELL > " END);
	if (!*input)
		return (printf("exiting\n"), 0);
	if (*input && input)
		add_history(*input);
	return (1);
}

static void	main_loop(void)
{
	char	*input;
	t_token	*tokens;

	input = NULL;
	while (1)
	{
		if (!read_input(&input))
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
}

int	main(void)
{
	main_loop();
	return (0);
}

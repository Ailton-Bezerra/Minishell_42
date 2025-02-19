/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/12 16:24:22 by cabo-ram         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_token		*tokens;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	env_list = convert_envp_to_env_list(envp);
	if (!env_list)
		return (1);
	while (1)
	{
		if (!read_input(&input))
			break ;
		tokens = tokenizer(input);
		if (tokens)
		{
			if (!internal_command(tokens, env_list))
				execute_pipe(tokens, envp);
		}
		// print_tokens(tokens);
		free(input);
		print_tokens(tokens);
		free_tokens(tokens);
	}
	rl_clear_history();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/15 14:31:36 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*read_input(void)
{
	char	*input;

	input = readline(YELLOW "MINISHEL > " END);
	if (!input)
	{
		printf("exiting\n");
		return (NULL);
	}
	if (*input && input)
		add_history(input);
	return (input);
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
		input = read_input();
		if (!input)
			break ;
		tokens = tokenizer(input);
		if (tokens)
		{
			if (!internal_command(tokens, env_list))
				execute_pipe(tokens, envp);
		}
		// print_tokens(tokens);
		free(input);
		free_tokens(tokens);
	}
	free_env_list(env_list);
	rl_clear_history();
	return (0);
}

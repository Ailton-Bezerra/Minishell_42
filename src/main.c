/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/21 14:40:18 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

void	init_minishell(t_env_list *env_list)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	minishell->env_list = env_list;
}

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
	init_minishell(env_list);
	while (1)
	{
		if (!read_input(&input))
			break ;
		gc_track(input);
		tokens = tokenizer(input);
		print_tokens(tokens);
		if (tokens)
		{
			if (!internal_command(tokens, env_list))
			{
				execute_pipe(tokens, envp);
			}
			gc_dealocate(input);
		}
	}
	gc_cleanup();
	rl_clear_history();
}

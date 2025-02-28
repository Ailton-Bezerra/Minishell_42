/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/28 10:30:18 by cabo-ram         ###   ########.fr       */
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
	minishell->exit_status = 0;
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

static void	main_loop(t_env_list *env_list, char **envp)
{
	char		*input;
	t_token		*tokens;

	while (1)
	{
		if (!read_input(&input))
			break ;
		gc_track(input);
		tokens = tokenizer(input);
		print_tokens(tokens);
		if (tokens)
		{
			if (!internal_command(tokens, env_list, ac, av))
			{
				process_pipes(tokens, env_list, envp);
			}
			gc_dealocate(input);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	env_list = convert_envp_to_env_list(envp);
	if (!env_list)
		return (1);
	init_minishell(env_list);
	main_loop(env_list, envp);
	gc_cleanup();
	rl_clear_history();
	return (0);
}

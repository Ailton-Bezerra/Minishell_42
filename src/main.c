/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/19 15:03:47 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	*get_ms(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

void	init_minishell(t_env *env_list)
{
	get_ms()->env_list = env_list;
	get_ms()->tokens = NULL;
	get_ms()->exit_status = 0;
	get_ms()->hd = init_hd(get_ms()->tokens);
	get_ms()->input_save = dup(STDIN_FILENO);
	get_ms()->output_save = dup(STDOUT_FILENO);
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

static void	main_loop(t_env *env_list)
{
	char		*input;
	t_token		*tokens;
	char		**t_env;

	t_env = get_ms()->env_list->var;
	while (1)
	{
		receive_signal();
		if (!read_input(&input))
			break ;
		tokens = tokenizer(input);
		get_ms()->tokens = tokens;
		// print_tokens(tokens);
		if (tokens)
		{
			if (!redirects(tokens, env_list))
			{
				exec();
				// check_hd(tokens);
				// process_pipes(tokens, env_list, t_env);
				// dup2(get_ms()->input_save, STDIN_FILENO);
				// dup2(get_ms()->output_save, STDOUT_FILENO);
			}
			// print_hdlist();
			free(input);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = init_env(envp);
	if (!env_list)
		return (1);
	init_minishell(env_list);
	main_loop(env_list);
	gc_cleanup();
	close_fds();
	rl_clear_history();
	return (0);
}

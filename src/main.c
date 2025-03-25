/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/25 09:57:21 by cabo-ram         ###   ########.fr       */
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
	// struct termios term;

	get_ms()->env_list = env_list;
	get_ms()->tokens = NULL;
	get_ms()->exit_status = 0;
	get_ms()->hd = init_hd(get_ms()->tokens);

	// essa parte pode ser substituida pelo save do io com tcg/tcs
	// get_ms()->input_save = dup(STDIN_FILENO);
	// get_ms()->output_save = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &get_ms()->original_term);

	get_ms()->child_pids = NULL;
	get_ms()->count_pids = 0;
	get_ms()->cmd_list = NULL;
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
	// struct		termios term;

	(void)env_list;
	t_env = get_ms()->env_list->var;
	while (1)
	{
		receive_signal();
		if (!read_input(&input))
			break ;
		tokens = tokenizer(input);
		// print_tokens(tokens);
		if (tokens)
		{
			get_ms()->tokens = tokens;
				// check_hd(tokens);
			exec();

			// essa parte pode ser substituda pela restauração io padrão com tcg/tcs
			// dup2(get_ms()->input_save, STDIN_FILENO);
			// dup2(get_ms()->output_save, STDOUT_FILENO);
			tcsetattr(STDIN_FILENO, TCSANOW, &get_ms()->original_term);

			free(input);
		}
	}
}

int	main(void)
{
	t_env	*env_list;

	env_list = init_env(__environ);
	if (!env_list)
		return (1);
	init_minishell(env_list);
	main_loop(env_list);
	clear_all();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:16:23 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/27 18:45:08 by ailbezer         ###   ########.fr       */
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

static void	main_loop(void)
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
		gc_track(input);
		tokens = tokenizer(input);
		if (tokens)
		{
			get_ms()->tokens = tokens;
			check_hd(tokens);
			exec();
			tcsetattr(STDIN_FILENO, TCSANOW, &get_ms()->original_term);
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
	main_loop();
	clear_all();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:34:53 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/27 11:23:26 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	internal_command(t_token *tokens, t_env_list *env_list)
// {
// 	char	**args;
// 	int		arg_count;

// 	if (!tokens || !tokens->value)
// 		return (0);
// 	arg_count = count_args(tokens);
// 	args = get_args(tokens, arg_count);
// 	if (!args)
// 		return (1);
// 	if (builtin(args[0]))
// 	{
// 		if (!ft_strncmp(args[1], ">", 1))
// 			handle_output_redirection(args[2], 0);
// 		execute_builtin(args, env_list);
// 		return (1);
// 	}
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:14:41 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/24 16:14:13 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**prepare_command(t_token *tokens)
{
	int			arg_count;
	char		**args;

	if (!tokens || !tokens->value)
		return (NULL);
	arg_count = count_args(tokens);
	args = get_args(tokens, arg_count);
	if (!args)
		return (NULL);
	return (args);
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type == WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

char	**get_args(t_token *tokens, int count)
{
	char	**args;
	int		i;

	i = 0;
	args = gc_malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("Error");
		return (NULL);
	}
	i = 0;
	while (tokens && tokens->type == WORD)
	{
		args[i] = ft_strdup(tokens->value);
		if (!args[i])
		{
			perror("Error");
			return (NULL);
		}
		tokens = tokens->next;
		i++;
	}
	args[count] = NULL;
	return (args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:14:41 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/21 14:42:22 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	print_error(char *cmd)
{
	ft_putstr_fd("Error: Missing argument\n", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

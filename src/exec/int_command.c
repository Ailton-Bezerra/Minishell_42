/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:34:53 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/10 17:35:09 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	internal_command(t_token *tokens, char **envp)
{
	char	**args;
	int		i;
	t_token	*temp;

	i = 0;
	temp = tokens;
	if (!tokens || !tokens->value)
		return (0);
	while (temp && temp->type == WORD)
	{
		i++;
		temp = temp->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
	{
		perror("Error");
		return (1);
	}
	temp = tokens;
	i = 0;
	while (temp && temp->type == WORD)
	{
		args[i] = ft_strdup(temp->value);
		if (!args[i])
		{
			perror("Error");
			free_array(args);
			return (1);
		}
		temp = temp->next;
		i++;
	}
	args[i] = NULL;
	if (builtin(args[0]))
	{
		execute_builtin(args, envp);
		free_array(args);
		return (1);
	}
	free_array(args);
	return (0);
}

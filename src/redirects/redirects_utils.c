/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:13:06 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/25 09:17:18 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*infile(t_token *token)
{
	char	*infile;

	infile = token->next->value;
	if (open(infile, O_RDONLY) == -1)
	{
		perror("minishell");
		return ("error");
	}
	return (infile);
}

char	*outfile(t_token *token)
{
	char	*outfile;

	outfile = token->next->value;
	if (token->type == APPEND)
	{
		if (open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644) == -1)
		{
			perror("minishell");
			return ("error");
		}
	}
	else
	{
		if (open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
		{
			perror("minishell");
			return ("error");
		}
	}
	return (outfile);
}

void	remove_redirection(t_token *prev, t_token *curr)
{
	t_token	*file;
	t_token	**t;

	t = &get_ms()->tokens;
	file = curr->next;
	if (prev)
		prev->next = file->next;
	else
		*t = file->next;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:13:06 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/28 15:19:08 by ailbezer         ###   ########.fr       */
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

char	*delimiter(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp->next)
	{
		if (temp->type == HERE_DOC)
			break ;
		temp = temp->next;
	}
	return (temp->next->value);
}

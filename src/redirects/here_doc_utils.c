/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:08:04 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/25 16:16:17 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	delimiter_quotes(char *dlmt)
{
	int	i;
	int	single_quote;
	int	double_quote;
	int	has_quotes;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	has_quotes = 0;
	while (dlmt[i])
	{
		if (dlmt[i] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			has_quotes = 1;
		}
		else if (dlmt[i++] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			has_quotes = 1;
		}
	}
	if (has_quotes)
		return (1);
	return (0);
}

char	*handle_expansion_hd(char *input)
{
	t_expand	ex;

	ex_init(&ex);
	while (input[ex.index])
	{
		if (input[ex.index] == '$' && input[ex.index + 1] == '?')
			input = expand_exit_status(input);
		else if (input[ex.index] == '$')
			input = expand_variable(input, &ex);
		else
			ex.index++;
	}
	return (input);
}

void	hd_eof(char *delimiter)
{
	ft_putstr_fd("Minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	exit(0);
}

void	ctrl_c_hd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

char *remove_dlmt_quotes(char *dlmt)
{
	char *new_dlmt;
	
	new_dlmt = NULL;
	if (dlmt[0] == '\'' && dlmt[(int)ft_strlen(dlmt) - 1] == '\'')
		new_dlmt = ft_strtrim(dlmt, "\'");
	else if (dlmt[0] == '\"' && dlmt[(int)ft_strlen(dlmt) - 1] == '\"')
		new_dlmt = ft_strtrim(dlmt, "\"");;
	return (new_dlmt);
}
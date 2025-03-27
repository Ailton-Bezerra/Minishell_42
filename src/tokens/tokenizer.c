/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:34:36 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/27 16:40:43 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_space(char **str, char **new_str, int *i, int flag)
{	
	*new_str = ft_strjoin(*new_str, ft_substr(*str, 0, *i));
	*new_str = ft_strjoin(*new_str, ft_strdup(" "));
	*new_str = ft_strjoin(*new_str, ft_substr(*str, *i, flag));
	*new_str = ft_strjoin(*new_str, ft_strdup(" "));
	*str = ft_substr(*str, *i + flag, ft_strlen(*str) - *i);
	*i = 0;
}

static void	change_qflag(const char *input, t_expand *ex, int i)
{
	if (input[i] == '\"' && !ex->d_quote)
		ex->d_quote = 1;
	else if (input[i] == '\"' && ex->d_quote)
		ex->d_quote = 0;
	if (input[i] == '\'' && !ex->quote)
		ex->quote = 1;
	else if (input[i] == '\'' && ex->quote)
		ex->quote = 0;
}

static char	*separe_simbols(const char *input)
{
	char		*s;
	char		*new_str;
	t_expand	ex;

	s = ft_strdup(input);
	ex_init(&ex);
	new_str = ft_strdup("");
	while (s && s[ex.i])
	{
		if (s[ex.i] == '\'' || s[ex.i] == '\"')
			change_qflag(input, &ex, ex.i);
		if ((!ft_strncmp(s + ex.i, "<<", 2) || !ft_strncmp(s + ex.i, ">>", 2))
			&& (!ex.quote && !ex.d_quote))
			add_space(&s, &new_str, &ex.i, 2);
		else if ((((s[ex.i] == '>' && (ex.i == 0
							|| s[ex.i - 1] != '>') && (s[ex.i + 1] != '>'))
					|| (s[ex.i] == '<' && (ex.i == 0 || s[ex.i - 1] != '<')
						&& (s[ex.i + 1] != '<')) || (s[ex.i] == '|'))
				&& (!ex.quote && !ex.d_quote)))
			add_space(&s, &new_str, &ex.i, 1);
		else
			ex.i++;
	}
	new_str = ft_strjoin(new_str, s);
	return (new_str);
}

t_token	*tokenizer(const char *input)
{
	t_token	*token_list;
	char	*input_norm;	

	input_norm = separe_simbols(input);
	token_list = handle_quotes(input_norm, NULL);
	if (!check_sintax(token_list))
		return (NULL);
	clear_quotes(token_list);
	return (token_list);
}

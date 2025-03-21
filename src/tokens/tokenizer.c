/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:34:36 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/21 17:02:29 by ailbezer         ###   ########.fr       */
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

static void change_qflag(const char *input, t_expand *ex, int i)
{
	if (input[i] == '\"' && !ex->double_quote)
		ex->double_quote = 1;
	else if (input[i] == '\"' && ex->double_quote)
		ex->double_quote = 0;
	if (input[i] == '\'' && !ex->quote)
		ex->quote = 1;
	else if (input[i] == '\'' && ex->quote)
		ex->quote = 0;
}


static char	*separe_simbols(const char *input)
{
	// size_t	i;
	char	*str;
	char	*new_str;
	t_expand	ex;

	ex_init(&ex);
	// i = 0;
	str = ft_strdup(input);
	new_str = ft_strdup("");
	while (str && str[ex.index])
	{
		if (str[ex.index] == '\'' || str[ex.index] == '\"')
			change_qflag(input, &ex, ex.index);
		if ((!ft_strncmp(str + ex.index, "<<", 2) || !ft_strncmp(str + ex.index, ">>", 2)) && (!ex.quote && !ex.double_quote))
			add_space(&str, &new_str, &ex.index, 2);
		else if ((((str[ex.index] == '>' && (ex.index == 0 || str[ex.index - 1] != '>')
				&& (str[ex.index + 1] != '>'))
			|| (str[ex.index] == '<' && (ex.index == 0 || str[ex.index - 1] != '<')
				&& (str[ex.index + 1] != '<')) || (str[ex.index] == '|')) && (!ex.quote && !ex.double_quote))
		)
			add_space(&str, &new_str, &ex.index, 1);
		else
			ex.index++;
	}
	new_str = ft_strjoin(new_str, str);
	return (new_str);
}

t_token	*tokenizer(const char *input)
{
	t_token	*token_list;
	char	*input_norm;	

	input_norm = separe_simbols(input);
	token_list = handle_quotes(input_norm, NULL);
	if (!chek_sintax(token_list))
		return (NULL);
	return (token_list);
}

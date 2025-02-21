/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:34:36 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/21 14:39:15 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_space(char **str, char **new_str, size_t *i, int flag)
{	
	*new_str = ft_strjoin(*new_str, ft_substr(*str, 0, *i));
	*new_str = ft_strjoin(*new_str, ft_strdup(" "));
	*new_str = ft_strjoin(*new_str, ft_substr(*str, *i, flag));
	*new_str = ft_strjoin(*new_str, ft_strdup(" "));
	*str = ft_substr(*str, *i + flag, ft_strlen(*str) - *i);
	*i = 0;
}

/**
 * @brief   Separates special symbols by adding spaces around them.
 * 
 * @param   input  The input string containing commands and operators.
 * 
 * @return  A new string where the operators '<<', '>>', '<', '>', and '|'
 *          are separated by spaces or NULL in case of malloc failure.
 */
static char	*separe_simbols(const char *input)
{
	size_t	i;
	char	*str;
	char	*new_str;

	i = 0;
	str = ft_strdup(input);
	new_str = ft_strdup("");
	while (str && str[i])
	{
		if (!ft_strncmp(str + i, "<<", 2) || !ft_strncmp(str + i, ">>", 2))
			add_space(&str, &new_str, &i, 2);
		else if (
			(str[i] == '>' && (i == 0 || str[i - 1] != '>')
				&& (str[i + 1] != '>'))
			|| (str[i] == '<' && (i == 0 || str[i - 1] != '<')
				&& (str[i + 1] != '<')) || (str[i] == '|')
		)
			add_space(&str, &new_str, &i, 1);
		else
			i++;
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

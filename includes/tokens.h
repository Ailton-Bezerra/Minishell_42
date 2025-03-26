/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:10:40 by ailbezer          #+#    #+#             */
/*   Updated: 2025/03/25 18:37:10 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

enum e_token
{
	WORD,
	PIPE,
	APPEND,
	TRUNC,
	INPUT,
	HERE_DOC,
	COMMAND,
	OPTION,
	FD,
};

typedef struct s_expand
{
	int		quote;
	int		d_quote;
	char	*var_value;
	int		var_len;
	int		i;
}			t_expand;

typedef struct s_token
{
	char			*value;
	enum e_token	type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

enum e_token	define_types(char *type);

#endif
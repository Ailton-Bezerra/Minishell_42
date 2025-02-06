/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/06 17:17:03 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libraries/libft/libft.h"

// # define PROMPT "minishell>$ "

// void	minishell_loop(void);

enum e_token
{
	WORD,
	PIPE,
	APPEND,
	TRUNC,
	INPUT,
	HERE_DOC,
};

typedef struct s_token
{
	char			*value;
	enum e_token	type;
	// bool			command;
	// struct s_token	*prev;
	struct s_token	*next;
}					t_token;

// ============== tokens/tokenizer ==============
t_token			*tokenizer(const char *input);

// ============== tokens/token_list ==============
t_token			*new_token_node(char *content);
void			add_token(t_token **head, char *content);

// ============== tokens/types ==============
enum e_token	define_types(char *type);

// ============== debug/print_tokens ==============
void			print_tokens(t_token *token);

// ============== tokens/free_memory ==============
void			free_tokens(t_token *tokens);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_substr_free(char *s, unsigned int start, size_t end);

// ============== tokens/quotes ==============
t_token			*handle_quotes(char *line, t_token *tokens);

#endif
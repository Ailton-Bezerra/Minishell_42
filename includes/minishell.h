/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/08 13:47:32 by ailbezer         ###   ########.fr       */
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
# include "tokens.h"

// # define PROMPT "minishell>$ "

// void	minishell_loop(void);

# define YELLOW "\001\033[1;33m\002"
# define END "\001\033[0m\002"

// ============== tokens/tokenizer ==============
t_token			*tokenizer(const char *input);

// ============== tokens/token_list ==============
t_token			*new_token_node(char *content);
void			add_token(t_token **head, char *content);

// ============== tokens/types ==============
enum e_token	define_types(char *type);
void			command_type(t_token *tokens);

// ============== debug/print_tokens ==============
void			print_tokens(t_token *token);

// ============== tokens/free_memory ==============
void			free_tokens(t_token *tokens);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_substr_free(char *s, unsigned int start, size_t end);

// ============== tokens/quotes ==============
t_token			*handle_quotes(char *line, t_token *tokens);

// ============== tokens/sintax ==============
int				chek_sintax(t_token *tokens);

char			*handle_expansion(char *input);

#endif
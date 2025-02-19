/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/19 10:55:40 by ailbezer         ###   ########.fr       */
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
# include "garbage_collector.h"

# define YELLOW "\001\033[1;33m\002"
# define END "\001\033[0m\002"

// ============== tokens/tokenizer ==============
t_token			*tokenizer(const char *input);

// ============== tokens/token_list ==============
t_token			*new_token_node(char *content /*, char quote*/);
void			add_token(t_token **head, char *content/*, char quote*/);

// ============== tokens/types ==============
enum e_token	define_types(char *type);
void			command_type(t_token *tokens);

// ============== debug/print_tokens ==============
void			print_tokens(t_token *token);

// ============== tokens/quotes ==============
t_token			*handle_quotes(char *line, t_token *tokens);
char			*strip_outer_quotes(char *str);

// ============== tokens/sintax ==============
int				chek_sintax(t_token *tokens);

// ============== tokens/expansion ==============
char			*handle_expansion(char *input);


#endif
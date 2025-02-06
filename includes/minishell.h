/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/06 09:52:01 by cabo-ram         ###   ########.fr       */
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

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}					t_token;

//============ tokens_utils ===========
void	add_token(t_token **head, char *content);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);
// t_token	*tokenizer_input(const char *input);

//============== tokens ==============
// int		parse_quotes(const char *line, t_token **tokens_head);
// t_token	*split_tokens(const char *input);
t_token *tokenize(char *line, t_token *tokens);

#endif
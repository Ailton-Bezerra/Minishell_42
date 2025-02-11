/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/11 16:02:42 by cabo-ram         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include "../libraries/libft/libft.h"

// # define PROMPT "minishell>$ "

// void	minishell_loop(void);

# define YELLOW "\001\033[1;33m\002"
# define END "\001\033[0m\002"

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

// ============== exec/check_command.c ==============
int				internal_command(t_token *tokens, char **envp);

// ============== exec/execute_command.c ==============
void			execute_command(t_token *tokens, char **envp);

// ============== exec/find_path.c ==============
char			*get_path(char *cmd, char **envp);
void			execute(char *av, char **envp);

// ============== exec/pipe.c ==============
void			execute_pipe(t_token *tokens, char **envp);

// ============== exec/utils.c ==============
int				count_args(t_token *tokens);
char			**get_args(t_token *tokens, int count);
void			free_array(char **arr);
void			error(void);
void			print_error(char *cmd);

// ============== /builtin/builtin.c ==============
int				builtin(char *cmd);
void			ft_echo(char **cmd);
void			ft_cd(char **cmd);
void			ft_pwd(void);
// void			ft_export(char **cmd);
// void			ft_unset(char **cmd);
void			ft_env(char **envp);
void			execute_builtin(char **cmd, char **envp);

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
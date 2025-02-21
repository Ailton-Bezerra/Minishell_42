/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/02/21 12:23:09 by cabo-ram         ###   ########.fr       */
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
# include "tokens.h"
# include "garbage_collector.h"

# define YELLOW "\001\033[1;33m\002"
# define END "\001\033[0m\002"

typedef struct s_env_list
{
	char				**var;
	int					count;
	struct s_env_list	*next;
}				t_env_list;

// ============== /builtin/builtin_utils.c ==============
void			free_env_list(t_env_list *env_list);
t_env_list		*convert_envp_to_env_list(char **envp);

typedef struct s_minishell
{
	t_env_list	*env_list;
}				t_minishell;

// ============== /builtin/builtin.c ==============
int				builtin(char *cmd);
void			execute_builtin(char **cmd, t_env_list *env_list);

// ============== /builtin/cd.c ==============
void			ft_cd(char **cmd);

// ============== /builtin/echo.c ==============
void			ft_echo(char **cmd);

// ============== /builtin/env.c ==============
void			ft_env(t_env_list *env_list);

// ============== /builtin/exit.c ==============
void			ft_exit(char **cmd);

// ============== /builtin/export_utils.c ==============
int				check_valid_env_name(const char *arg);
void			free_var(char *var_name, char *var_value);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);

// ============== /builtin/export.c ==============
int				ft_export(t_env_list *env, char *arg);

// ============== /builtin/pwd.c ==============
void			ft_pwd(void);

// ============== /builtin/unset.c ==============
void			ft_unset(t_env_list **env, const char *var);

// ============== exec/check_command_utils.c ==============
char			*get_command_path(char *cmd, char **envp);
void			fork_error(char *path, char **args);

// ============== exec/check_command.c ==============
int				internal_command(t_token *tokens, t_env_list *env_list);

// ============== exec/exec_utils.c ==============
int				count_args(t_token *tokens);
char			**get_args(t_token *tokens, int count);
void			free_array(char **arr, int index);
void			error(void);
void			print_error(char *cmd);

// ============== exec/execute_command_utils.c ==============
char			*get_command_path(char *cmd, char **envp);

// ============== exec/execute_command.c ==============
void			execute_command(t_token *tokens, char **envp);

// ============== exec/find_path.c ==============
char			*get_path(char *cmd, char **envp);
void			execute(char *av, char **envp);

// ============== exec/pipe.c ==============
t_token			*find_pipe(t_token *tokens);
void			child_process(t_token *tokens, char **envp, int input_fd,
					int fd[2]);
void			parent_process(t_token *tokens, char **envp, int output_fd,
					int fd[2]);
void			run_pipeline(t_token *tokens, char **envp, int input_fd,
					int output_fd);
void			process_pipes(t_token *tokens, char **envp);

// ============== tokens/tokenizer ==============
t_token			*tokenizer(const char *input);

// ============== tokens/token_list ==============
t_token			*new_token_node(char *content);
void			add_token(t_token **head, char *content);
void			process_token(t_token **tokens, char *line, int *i);

// ============== tokens/types ==============
enum e_token	define_types(char *type);
void			command_type(t_token *tokens);

// ============== debug/print_tokens ==============
void			print_tokens(t_token *token);

// ============== tokens/quotes ==============
char			*ft_strndup(const char *s, size_t n);
t_token			*handle_quotes(char *line, t_token *tokens);
char			*remove_outer_quotes(char *input, int single_q, int double_q);

// ============== tokens/sintax ==============
int				chek_sintax(t_token *tokens);

// ============== tokens/expansion ==============
char			*handle_expansion(char *input);

t_minishell		*get_minishell(void);
void			init_minishell(t_env_list *env_list);
char			*ft_getenv(t_env_list *env, const char *name);
char			*get_value(const char *var);

#endif
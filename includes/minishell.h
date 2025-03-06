/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/06 16:27:15 by ailbezer         ###   ########.fr       */
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
# define CYAN	"\001\033[0;36m\002"
# define END	"\001\033[0m\002"

typedef struct s_env
{
	char				**var;
	int					count;
}				t_env;

// ============== /builtin/builtin_utils.c ==============
t_env		*init_env(char **envp);

typedef struct s_minishell
{
	t_env	*env_list;
	t_token		*tokens;
	int			exit_status;
	int			input_save;
	int			output_save;
}				t_minishell;

// ============== /builtin/builtin.c ==============
int				builtin(char *cmd);
void			execute_builtin(char **cmd, t_env *env_list);

// ============== /builtin/cd.c ==============
void			ft_cd(char **cmd);

// ============== /builtin/echo.c ==============
void			ft_echo(char **cmd);

// ============== /builtin/env.c ==============
void			ft_env(t_env *env_list, char **cmd);

// ============== /builtin/exit.c ==============
void			ft_exit(char **cmd);

// ============== /builtin/export_utils.c ==============
int				check_valid_env_name(const char *arg, const char *cmd);
void			free_var(char *var_name, char *var_value);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);

// ============== /builtin/export.c ==============
int				ft_export(t_env *env, char *arg);

// ============== /builtin/pwd.c ==============
void			ft_pwd(void);

// ============== /builtin/unset.c ==============
void			ft_unset(t_env **env, const char *var);

// ============== exec/check_command_utils.c ==============
char			*get_command_path(char *cmd, char **envp);

// ============== exec/check_command.c ==============
int				redirects(t_token *tokens, t_env *env_list);

// ============== exec/exec_utils.c ==============
int				count_args(t_token *tokens);
char			**get_args(t_token *tokens, int count);
void			free_array(char **arr, int index);
void			error(void);
void			print_error(char *cmd);

// ============== exec/execute_command_utils.c ==============
char			*get_command_path(char *cmd, char **envp);
void			fork_error(char *path, char **args);
t_token			*get_cmd_tokens(t_token *tokens);

// ============== exec/execute_command.c ==============
void			execute_command(t_token *tokens, t_env *env_list,
					char **t_env);

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
void			process_pipes(t_token *tokens, t_env *env_list, char **envp);

// ============== tokens/tokenizer.c ==============
t_token			*tokenizer(const char *input);

// ============== tokens/token_list.c ==============
t_token			*new_token_node(char *content);
void			add_token(t_token **head, char *content);
void			process_token(t_token **tokens, char *line, int *i);

// ============== tokens/types.c ==============
enum e_token	define_types(char *type);
void			command_type(t_token *tokens);

// ============== debug/print_tokens.c ==============
void			print_tokens(t_token *token);

// ============== tokens/quotes.c ==============
char			*ft_strndup(const char *s, size_t n);
t_token			*handle_quotes(char *line, t_token *tokens);
char			*remove_outer_quotes(char *input, int single_q, int double_q);

// ============== tokens/sintax.c ==============
int				chek_sintax(t_token *tokens);

// ============== tokens/expansion.c ==============
char			*handle_expansion(char *input);

// ============== tokens/ft_getenv.c ==============
char			*ft_getenv(t_env *env, const char *name);
char			*get_value(const char *var);

// ============== main.c ==============
t_minishell		*get_ms(void);
void			init_minishell(t_env *env_list);

// ============== dolar_question.c ==============
char			*expand_exit_status(char *token);

// ============== signal.c ==============
void			receive_signal(void);
void			cmd_signal(void);

// ============== output.c ==============
int				handle_output_redirection(char *filename, int append);

int	save_original_stdin(int *saved);
int	save_original_stdout(int *saved);
void	close_fds(void);

#endif
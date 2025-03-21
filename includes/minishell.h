/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/21 17:26:06 by ailbezer         ###   ########.fr       */
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
	char			**var;
	int				count;
	struct s_env	*next;
}					t_env;

// ============== /builtin/builtin_utils.c ==============
t_env		*init_env(char **envp);

typedef struct s_here_doc_list
{
	char					*filename;
	struct s_here_doc_list	*next;
}							t_hd_list;

typedef struct s_here_doc
{
	int			start_fd;
	int			cmd_index;
	t_hd_list	**arr_hds;
}				t_hd;

typedef struct s_command
{
	char				**args;
	char				*path;
	int					pipe_in;
	int					pipe_out;
	int					pipe_fd[2];
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_minishell
{
	t_env		*env_list;
	t_token		*tokens;
	t_hd		*hd;
	t_command	*cmd_list;
	int			exit_status;
	int			input_save;
	int			output_save;
	int			*child_pids;
	int			count_pids;
}				t_minishell;

// ============== /builtin/builtin.c ==============
int			builtin(char *cmd);
void		execute_builtin(char **cmd, t_env *env_list);

// ============== /builtin/cd.c ==============
void			ft_cd(char **cmd);

// ============== /builtin/echo.c ==============
void			ft_echo(char **cmd);

// ============== /builtin/env.c ==============
void			ft_env(t_env *env_list, char **cmd);

// ============== /builtin/exit.c ==============
void			ft_exit(char **cmd);

// ============== /builtin/export_utils_2.c ==============
int				ft_strcmp(const char *s1, const char *s2);
void			ft_swap(char **a, char **b);
void			sort_env_list(t_env *env_list);
void			ft_xp(t_env *env_list);

// ============== /builtin/export_utils.c ==============
int				is_valid_env(char c, int first_char);
int				check_valid_env_name(const char *arg, const char *cmd);
void			free_env_list(t_env *env_list);
void			free_var(char *var_name, char *var_value);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);

// ============== /builtin/export.c ==============
int				ft_export(t_env *env, char *arg);
void			ft_xp(t_env *env_list);

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
// void			execute_command(t_token *tokens, t_env *env_list,
// 					char **t_env);
char			**prepare_command(t_token *tokens);

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
enum e_token			define_types(char *type);
void					command_type(t_token *tokens);

// ============== debug/print_tokens.c ==============
void			print_tokens(t_token *token);
void			print_cmd_list(t_command *cmd_list);

// ============== tokens/quotes.c ==============
char			*ft_strndup(const char *s, size_t n);
t_token			*handle_quotes(char *line, t_token *tokens);
char			*remove_outer_quotes(char *input, int single_q, int double_q);

// ============== tokens/sintax.c ==============
int				chek_sintax(t_token *tokens);

// ============== tokens/expansion.c ==============
char			*handle_expansion(char *input);
void			ex_init(t_expand *ex);
char			*expand_variable(char *result, t_expand *ex);
void	change_quote_flag(const char *result, t_expand *ex, int *i);

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
void			ctrl_backslash(int sig);
void			ctrl_c(int sig);

// ============== output.c ==============
int				handle_output_redirection(char *filename, int append);

int	save_original_stdin(int *saved);
int	save_original_stdout(int *saved);
void	close_fds(void);

// ============== here_doc.c ==============
void	execute_hd(t_token *tokens);
char	*delimiter(t_token *tokens);
void	check_hd(t_token *tokens);

// ============== here_doc_utils.c ==============
char			*handle_expansion_hd(char *input);
void			hd_eof(char *delimiter);
void			ctrl_c_hd(int sig);

// ============== here_doc_list.c ==============
t_hd			*init_hd(t_token *tokens);
t_hd_list		*new_hd_node(char *filename);
t_hd_list 		*last_hd_node(t_hd_list *head);
void			append_hd(char *filename, t_hd_list **head);

int				delimiter_quotes(char *dlmt);

// ============== exec.c ==============
void			exec(void);
t_command	*creat_cmd_list(t_token *tmp_token);
void	cmd_pipeline(t_command *cmd_list);

// ============== command_list.c ==============
void	append_cmd(char **args, t_command **head, int pipe_in, int pipe_out);

// ============== exec_utils.c ==============
void	exec_external(t_command *cmd_list);
void 	wait_for_children(void);
int				count_pipes(t_token *tokens);

// ============== pipes.c ==============
void	creat_pipes(t_command *cmd_list);
void 	close_pipes(t_command *cmd_list, t_command *curr);
void	redirect_pipes(t_command *cmd);

#endif
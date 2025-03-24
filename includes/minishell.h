/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:51:22 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/03/24 16:16:17 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <termios.h>
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
	char			**copy;
	int				count;
	struct s_env	*next;
}					t_env;

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
	int					pipe_fd[2];
	int					pipe_out;
	char				*infile;
	int					infile_fd;
	char				*outfile;
	int					outfile_fd;
	int					fd_error;
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

// ============== /builtin/builtin_utils.c ==============
t_env		*init_env(char **envp);

// ============== /builtin/builtin.c ==============
int			builtin(char *cmd);
void		execute_builtin(char **cmd, t_env *env_list);

// ============== /builtin/cd.c ==============
void		ft_cd(char **cmd);

// ============== /builtin/echo.c ==============
void		ft_echo(char **cmd);

// ============== /builtin/env.c ==============
void		ft_env(t_env *env_list, char **cmd);

// ============== /builtin/exit.c ==============
void		ft_exit(char **cmd);

// ============== /builtin/export_utils_2.c ==============
int			ft_strcmp(const char *s1, const char *s2);
void		ft_swap(char **a, char **b);
void		sort_env_list(t_env *env_list);
void		ft_xp(t_env *env_list);

// ============== /builtin/export_utils.c ==============
int			is_valid_env(char c, int first_char);
int			check_valid_env_name(const char *arg, const char *cmd);
void		free_var(char *var_name, char *var_value);
void		free_env_list(t_env *env_list);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

// ============== /builtin/export.c ==============
int			ft_export(t_env *env, char *arg);

// ============== /builtin/pwd.c ==============
void		ft_pwd(void);

// ============== /builtin/unset.c ==============
void		ft_unset(t_env **env, const char *var);

// ============== exec/exec_utils.c ==============
int			count_args(t_token *tokens);
char		**get_args(t_token *tokens, int count);
void		print_error(char *cmd);

// ============== exec/check_command_utils.c ==============
char		*get_command_path(char *cmd, char **envp);

// ============== exec/execute_command.c ==============
char		**prepare_command(t_token *tokens);

// ============== exec/path.c ==============
char		*get_path(char *cmd, char **envp);

// ============== expansion/dolar_question.c ==============
char		*expand_exit_status(char *token);

// ============== expansion/expansion.c ==============
void		ex_init(t_expand *ex);
void		change_quote_flag(const char *result, t_expand *ex, int *i);
char		*expand_variable(char *result, t_expand *ex);
char		*handle_expansion(char *input);

// ============== expansion/ft_getenv.c ==============
char		*get_value(const char *var);
char		*ft_getenv(t_env *env, const char *name);

// ============== garbage_collector/close_fds.c ==============
void		close_fds(void);

// ============== new_exec/command_list.c ==============
t_command	*last_cmd_node(t_command *head);
t_command	*creat_cmd_list(t_token *tmp_token);

// ============== new_exec/exec_utils.c ==============
void		wait_for_children(void);
void		exec_external(t_command *cmd);
int			count_pipes(t_token *tokens);

// ============== new_exec/exec.c ==============
void		cmd_pipeline(t_command *cmd_list);
void		exec(void);

// ============== new_exec/pipes.c ==============
void		creat_pipes(t_command *cmd_list);
void		close_pipes(t_command *cmd_list, t_command *curr);
void		redirect_pipes(t_command *cmd);

// ============== new_exec/redirects.c ==============
int			get_outfile_fd(t_token *token, char *filename);
int			get_infile_fd(t_token *token, char *filename);
int			redirect_fds(t_command *cmd);
void		close_redirects(t_command *cmd);

// ============== redirects/here_doc_list.c ==============
t_hd		*init_hd(t_token *tokens);
t_hd_list	*new_hd_node(char *filename);
t_hd_list	*last_hd_node(t_hd_list *head);
void		append_hd(char *filename, t_hd_list **head);

// ============== redirects/here_doc_utils.c ==============
int			delimiter_quotes(char *dlmt);
char		*handle_expansion_hd(char *input);
void		hd_eof(char *delimiter);
void		ctrl_c_hd(int sig);

// ============== redirects/here_doc.c ==============
char		*delimiter(t_token *tokens);
void		hd_loop(t_token *tokens, char *dlmt, int fd);
void		hd_routine(t_token *tokens);
void		execute_hd(t_token *tokens);
void		check_hd(t_token *tokens);

// ============== signals/signal.c ==============
void		receive_signal(void);
void		ctrl_c(int sig);
void		ctrl_backslash(int sig);
void		cmd_signal(void);

// ============== tokens/quotes.c ==============
char		*ft_strndup(const char *s, size_t n);
char		*remove_outer_quotes(char *input, int single_q, int double_q);
t_token		*handle_quotes(char *line, t_token *tokens);

// ============== tokens/sintax.c ==============
int			check_sintax(t_token *tokens);

// ============== tokens/token_list.c ==============
t_token		*new_token_node(char *content);
void		add_token(t_token **head, char *content);
void		process_token(t_token **tokens, char *line, int *i);

// ============== tokens/tokenizer.c ==============
t_token		*tokenizer(const char *input);

// ============== tokens/types.c ==============
void		command_type(t_token *tokens);
enum e_token	define_types(char *type);

// ============== main.c ==============
t_minishell	*get_ms(void);
void		init_minishell(t_env *env_list);

// ============== debug/print_list.c ==============
void		print_tokens(t_token *token);
void		print_cmd_list(t_command *cmd_list);

// ============== cmd_list_utils.c ==============
char	*infile(t_token *token);
char	*outfile(t_token *token);
void	remove_redirection(t_token *prev, t_token *curr);

void clear_all(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:29:12 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/16 10:28:34 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell$ "
# define SUCCESS 0
# define ERROR 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define PATH_MAX 4096

extern int			g_signal_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_WHITESPACE
}					t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_exported;
}					t_env;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
}					t_redir;

typedef struct s_command
{
	char			**args;
	t_list			*redirections;
	int				is_builtin;
	pid_t			pid;
	int				in_fd;
	int				out_fd;
}					t_command;

typedef struct s_data
{
	t_list			*env_list;
	t_list			*command_list;
	int				last_exit_code;
	int				stdin_backup;
	int				stdout_backup;
}					t_data;

void				ms_init_data(t_data *data, char **envp);
void				ms_cleanup(t_data *data);
void				ms_save_io(t_data *data);
void				ms_restore_io(t_data *data);
t_list				*ms_create_env_list(char **envp);
char				*ms_get_env_value(t_list *env_list, const char *key);
void				ms_free_env_node(void *content);
void				ms_setup_signals(void);
void				ms_handle_sigint(int sig);
void				ms_signals_child(void);
void				ms_signals_heredoc(void);
void				ms_free_command_node(void *content);
void				ms_free_redir(void *content);
void				ms_error_exit(const char *msg, int exit_code);
void				ms_print_error(char *cmd, char *msg);

/*  Lexer  */

t_list				*ms_lexer(const char *line);
int					ms_is_whitespace(char c);
int					ms_is_separator(char c);
int					ms_is_special_char(char c);
int					ms_is_quote(char c);
int					ms_handle_quotes(const char *s, int i, char quote_type);
int					ms_has_unclosed_quotes(const char *str);
t_token				*ms_create_token(t_token_type type, char *value);
void				ms_free_token(void *content);
char				*ms_extract_word(const char *str, int *i);
char				*ms_extract_quoted(const char *str, int *i, char quote);
t_token				*ms_tokenize_operator(const char *str, int *i);
void				ms_print_tokens(t_list *tokens);

/* Parser */

t_list				*ms_parser(t_list *tokens);
int					ms_syntax_check(t_list *tokens);
t_command			*ms_create_command(void);
void				ms_add_argument(t_command *cmd, char *arg);
int					ms_add_redirection(t_command *cmd, t_list **current_token);
int					ms_setup_redirections(t_command *cmd);
int					ms_do_heredoc(t_redir *redir);
t_redir				*ms_create_redir(t_redir_type type, char *file);
int					ms_is_redir(t_token_type type);
int					ms_count_args(t_list *tokens);
t_command			*ms_build_single_command(t_list **tokens);

void				ms_expand_vars(t_data *data, t_command *cmd);
void				ms_remove_quotes(t_command *cmd);

/*  Builtins */

int					ms_is_builtin(char *cmd_name);
int					ms_run_builtin(t_data *data, t_command *cmd);
int					ms_builtin_env(t_list *env_list);
int					ms_builtin_echo(char **args);
int					ms_builtin_cd(t_data *data, char **args);
int					ms_builtin_unset(t_data *data, char **args);
int					ms_builtin_export(t_data *data, char **args);
int					ms_builtin_exit(t_data *data, char **args);

/*  Execution */

char				*ms_resolve_path(t_data *data, char *cmd);
void				ms_expand_command(t_data *data, t_command *cmd);
void				ms_execute_manager(t_data *data);
void				ms_execute_external(t_data *data, t_command *cmd);
void				ms_execute_fork(t_data *data, t_command *cmd);
void				ms_wait_all(t_data *data);
void				ms_execute_pipeline(t_data *data);

#endif
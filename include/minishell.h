/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:36:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/18 17:08:06 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>	// sigaction(), sigemptyset(), sigaddset(), kill()
# include <stdio.h>		// printf(), perror
# include <string.h>	// strerror()
# include <errno.h>		// errno
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>	// malloc()
# include <unistd.h>	// write(), fork()
# include <sys/wait.h>	// waitpid()
# include <fcntl.h>		// open()
# include <sys/stat.h>	// stat()
# include <termios.h>	// terminal device attributes: tcgetattr(), tcsetattr()

# include "libft.h"
# include "constants.h"

/* ------------------------------- Structures ------------------------------- */

typedef struct s_ast
{
	char			**value;
	t_tokentype		type;
	int				fd;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_flags
{
	bool			a;
	bool			b;
	bool			c;
}					t_flags;

typedef struct s_elem
{
	int				i;
	int				k;
	int				y;
	int				j;
	size_t			len;
	size_t			new_len;
	char			quote;
}					t_elem;

typedef struct s_index
{
	int				pip;
	int				key;
	int				min;
	int				max;
	int				len;

}					t_index;

typedef struct s_env
{
	char			**envp;
	unsigned int	len;
	unsigned int	capacity;	
}	t_env;

typedef struct s_mshell
{
	t_env			env;
	int				exit_code;
	char			*input;
	t_ast			*root;
	t_ast			*tmp_node;
	struct termios	term[2];
	t_bool			is_term_set;
}					t_mshell;

typedef struct s_token
{
	t_ast			**root;
	t_mshell		*ms;
	int				len;
	char			*value;
	char			**cmd;
	t_tokentype		type;
	bool			lock;
	bool			has_dollar;
	char			quote;
}					t_token;

/* -------------------------------- Signals -------------------------------- */

void		sig_to_exit_code(t_mshell *ms);
void		sig_interceptor(t_sig_mode mode);
void		sig_sigint_main(int sig);
int			sig_reset_readline(void);
int			sig_reset_heredoc_readline(void);
int			sig_set_termios(t_term term_type, t_mshell *ms);

/* ------------------------------ Environment ------------------------------ */

char		*env_find_variable(const char *var, t_env *env, size_t	*i);
const char	*env_find_value(const char *var, t_env *env);
int			env_add(const char *var, t_env *env);
int			env_remove(const char *var, t_env *env);

/* -------------------------------- Builtins ------------------------------- */

/// A command that is implemented internally by the shell itself, 
/// rather than by an executable program somewhere in the file system.

int			builtin_echo(char **args);
int			builtin_env(char **args, t_env *env);
int			builtin_unset(char **args, t_env *env);
int			builtin_export(char **args, t_env *env);
int			builtin_pwd(char **args, t_env *env);
int			builtin_exit(char **args, t_mshell *ms);
int			builtin_cd(char **args, t_env *env);

int			builtin_is_identifier_valid(const char *var);
void		builtin_update_env_var(const char *name, const char *value, \
									t_env *env);

/* -------------------------------- Execution ------------------------------ */

int			exe_ast_tree(t_ast *node, t_mshell *ms);
int			exe_pipe(t_ast *root, t_mshell *ms);
int			exe_command(t_ast *node, t_mshell *ms);
int			exe_heredoc_preprocessor(t_ast *node, t_mshell *ms);
int			exe_heredoc(t_ast *node, t_mshell *ms);
int			exe_redirection(t_ast *node, t_mshell *ms);

int			exe_wait_children(pid_t *pids, int amount);
void		exe_close_fd(int *fd);
char		*exe_search_cmd_path(const char *cmd, const char *env_path, \
								char *path);
void		exe_handle_dollar_expansion(char *input, int fd_write, \
										t_mshell *ms);
int			exe_handle_cmd_error(char *path);

/* ------------------------- Exit, errors and memory ----------------------- */

void		exit_destroy_minishell(t_mshell *ms);
void		free_environment(t_env *env);
void		free_2d_array(char **arr, int count);
void		exit_free(t_token *tokens, int len, char *buffer);

/* ------------------------------ Initialisation --------------------------- */

int			init_environment(char **envp_arr, t_env *env);
void		init_minishell_struct(t_mshell *ms, char **envp);
int			init_termios_attributes(t_mshell *ms);

/* ------------------------------ Parsing --------------------------- */

void		ft_bzero(void *s, size_t n);
char		*ft_strndup(char *s, size_t n);
t_ast		*create_node(char **s1, t_tokentype type, t_token *tokens);
int			tokenize(t_token *tokens, char *input);
t_ast		*parse_input(char *input, t_mshell *ms, int *exit_code);
void		assign_to_right(t_ast *root, t_token *tokens, t_index *i);
void		assign_to_left(t_ast *root, t_token *tokens, t_index *i, \
							bool flag);
void		find_root(t_ast **root, t_token *tokens, t_index *i);
void		free_tokens(t_token *tokens, int len);
void		free_ast(t_ast *node);
char		*deal_with_quotes(char *input, t_mshell *ms);
char		**create_cmd(char *s);
bool		compare_token(char *buffer, int i, bool flag, char quote);
char		quote_value(char c);
char		**cpy_cmds(char **strs);
char		*handle_dollar_sign(char *input, t_mshell *ms);
char		*env_find_variable_v2(const char *var, t_env *env, size_t *i);
char		*env_find_value_v2(const char *var, t_env *env);
bool		check_parse_error(t_token *tokens, int len);
char		*ft_strdup_no_op(char *str, size_t n);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:36:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/30 06:41:57 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @note Small things to do:
 * 
 * 1) Add function to init t_mshell minishell structure.
 * 2) exe_wait_children() should we specify the error message?
 * 4) heredoc: handle quotes and $ expansion
 * 5) check if rl_replace_line() or rl_redisplay() fail?
 * 6) exe_search_cmd_path should we add current directory to search?
 *    (case to run `minishell> ./minishell`)
 * 7) export _ seems to do nothing and return 0
 * 8) exe_ast_tree() - do we nee ARG node?
 * 
 * @bug: test case (comment)
 * 1) cat << l fgfg (parser ignores `fgfg` -> should be treated as a command)
 * 
 */


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
# include <stdbool.h>

# include "constants.h"
# include "structures.h"
# include "parsing.h"
# include "libft.h"

/* -------------------------------- Signals -------------------------------- */

void		sig_handler_main(int sig, siginfo_t *info, void *context);
void		sig_sigaction_init(struct sigaction *sa, \
								void (*handler) (int, siginfo_t *, void *));
void		sig_child_process_handler(t_sig_mode sig_mode);

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
int 		builtin_unset(char **args, t_env *env);
int			builtin_export(char **args, t_env *env);
int			builtin_pwd(char **args);
int			builtin_exit(char **args, t_mshell *ms);
int			builtin_cd(char **args, t_env *env);

int			builtin_is_identifier_valid(const char *var);
void		builtin_update_env_var(const char *name, const char *value, \
									t_env *env);

/* -------------------------------- Execution ------------------------------ */

int			exe_ast_tree(t_ast *node, t_mshell *ms);
int			exe_pipe(t_ast *root, t_mshell *ms);
int			exe_command(t_ast *node, t_mshell *ms);
int			exe_heredoc(t_ast *node, t_mshell *ms);
int			exe_redirection(t_ast *node, t_mshell *ms);

int			exe_wait_children(pid_t *pids, int amount);
void		exe_close_fd(int *fd);
char		*exe_search_cmd_path(const char *cmd, const char *env_path, \
								char *path);
int			exe_check_special_case(char **args, t_mshell *ms);

/* ------------------------- Exit, errors and memory ----------------------- */

void		exit_destroy_minishell(t_mshell *ms);
void		free_environment(t_env *env);
void		free_2d_array(char **arr, int count);

/* ------------------------------ Initialisation --------------------------- */

int			init_environment(char **envp_arr, t_env *env);
void		init_minishell_struct(t_mshell *ms, char **envp);

#endif
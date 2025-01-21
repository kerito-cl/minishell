/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:36:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/21 19:40:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @note Small things to do:
 * 
 * 1) Setup uniform error handling system for builtins.
 * 2) Check the original error codes for builtins.
 * 3) Add function to init t_mshell minishell structure.
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

# include "constants.h"
# include "structures.h"
# include "libft.h"

/* -------------------------------- Signals -------------------------------- */

void		sig_handler_main(int sig, siginfo_t *info, void *context);
void		sig_sigaction_init(struct sigaction *sa, \
								void (*handler) (int, siginfo_t *, void *));

/* ------------------------------ Environment ------------------------------ */

void		env_free(t_env *env);
int			env_init(char **envp_arr, t_env *env);
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

/* ------------------------- Exit, errors and memory ----------------------- */

void		exit_destroy_minishell(t_mshell *ms);

#endif
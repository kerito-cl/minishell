/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:36:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/18 17:06:15 by ipersids         ###   ########.fr       */
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
# include <unistd.h>

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

int			builtin_is_identifier_valid(const char *var);

#endif
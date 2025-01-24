/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:41:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 15:36:41 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <limits.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

extern volatile sig_atomic_t	g_status;

typedef enum e_error_code
{
	ERROR_GENERIC = 1,
	ERROR_INVALID_OPTION,
	ERROR_BUILTIN_EXIT_TOO_MANY_ARGS = 1,
	ERROR_SIGACTION_FAILS = 100,
	ERROR_MALLOC_FAILS,
	ERROR_NULL_INPUT,
	ERROR_BUILTIN_ENV_ARGS,
	ERROR_BUILTIN_EXPORT_INV_VAR,
	ERROR_BUILTIN_UNSET_INV_VAR,
	ERROR_BUILTIN_PWD_ARGS,
	ERROR_BUILTIN_GETCWD_FAILS,
	ERROR_CMD_NOT_FOUND = 127,
	ERROR_BUILTIN_EXIT_INVALID_ARG = 255
}	t_error_code;

# ifndef FD_READ
#  define FD_READ 0
# endif

# ifndef FD_WRITE
#  define FD_WRITE 1
# endif

# ifndef FORK_LEFT
#  define FORK_LEFT 0
# endif

# ifndef FORK_RIGHT
#  define FORK_RIGHT 1
# endif

#endif
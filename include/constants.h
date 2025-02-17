/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:41:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/17 09:41:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <limits.h>
# include <stdbool.h>

extern volatile sig_atomic_t	g_status;

typedef enum e_error_code
{
	ERROR_GENERIC = 1,
	ERROR_INVALID_OPTION = 2,
	ERROR_MALLOC_FAILS = 12,
	ERROR_ISDIR = 126,
	ERROR_CMD_NOT_FOUND = 127,
	ERROR_INTERUPTED_SIGINT = 130,
	ERROR_INVALID_EXIT_CODE = 255,
	ERROR_SYNTAX_HEREDOC = 258,
	ERROR_IGNORE = 1024
}	t_error_code;

typedef enum e_sig_mode
{
	SIG_INTERACTIVE_MODE,
	SIG_HEREDOC_MODE,
	SIG_DEFAULT_MODE
}	t_sig_mode;

typedef enum e_tokentype
{
	PIPE = 22,
	REIN,
	REIN2,
	REOUT,
	REOUT2,
	ARG,
	CMD,
}	t_tokentype;

typedef enum e_term
{
	TERM_ORIGIN,
	TERM_ECHOCTL
}	t_term;

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define FD_READ 0
# define FD_WRITE 1
# define FORK_LEFT 0
# define FORK_RIGHT 1
# define EXIT_CODE_CASE "$?"
# define SIGINT_CHAR "^C"
# define ADD_CAPACITY 100

#endif
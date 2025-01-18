/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:41:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/18 18:25:40 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <limits.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

extern volatile int	g_status;

typedef enum e_error_code
{
	ERROR_SIGACTION_FAILS = 100,
	ERROR_MALLOC_FAILS,
	ERROR_NULL_INPUT,
	ERROR_BUILTIN_ENV_ARGS,
	ERROR_BUILTIN_EXPORT_INV_VAR,
	ERROR_BUILTIN_UNSET_INV_VAR,
	ERROR_BUILTIN_PWD_ARGS,
	ERROR_BUILTIN_GETCWD_FAILS
}	t_error_code;

#endif
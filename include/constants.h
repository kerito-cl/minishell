/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:41:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/18 17:11:39 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

extern volatile int	g_status;

typedef enum e_error_code
{
	ERROR_SIGACTION_FAILS = 100,
	ERROR_MALLOC_FAILS,
	ERROR_NULL_INPUT,
	ERROR_BUILTIN_ENV_ARGS,
	ERROR_BUILTIN_EXPORT_INV_VAR,
	ERROR_BUILTIN_UNSET_INV_VAR,
}	t_error_code;

#endif
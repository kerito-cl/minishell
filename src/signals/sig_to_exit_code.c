/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_to_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:21:48 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/16 12:03:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Converts signal status to exit code.
 * 
 * @param ms The minishell context.
 */
void	sig_to_exit_code(t_mshell *ms)
{
	if (g_status == 128 + SIGINT)
		ms->exit_code = ERROR_INTERUPTED_SIGINT;
	else if (g_status != 0)
		ms->exit_code = g_status + 128;
	g_status = 0;
}

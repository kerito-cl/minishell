/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:41:24 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/30 20:15:53 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Signal handler for the main shell process.
 * 
 * This function handles signals for the main shell process. It handles SIGINT 
 * and SIGQUIT signals. For SIGINT, it sets the global status, writes a newline,
 * replaces the current line, and redisplays the prompt. For SIGQUIT, it sets 
 * the global status and returns.
 * 
 * @param sig The signal number.
 * @param info Pointer to the structure containing signal info (unused).
 * @param context Pointer to the context information (unused).
 */
void	sig_handler_main(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (SIGINT == sig)
	{
		g_status = sig;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (SIGQUIT == sig)
		g_status = sig;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:41:24 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/16 12:02:17 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Signal SIGINT handler for the main shell process.
 * 
 * It sets the global status, simulate a newline input,
 * replaces the current line, and redisplays the prompt.
 * 
 * @param sig The signal number.
 */
void	sig_sigint_main(int sig)
{
	if (sig == SIGINT)
		g_status = SIGINT;
}

/**
 * @brief Resets the readline state if SIGINT was received.
 * 
 * This function checks if the global status indicates that a SIGINT
 * signal was received. If so, it resets the status, writes a newline
 * to the standard output, replaces the current line in the readline
 * buffer with an empty string, moves the cursor to a new line, and
 * redisplays the prompt.
 * 
 * @return int Always returns 0.
 */
int	sig_reset_readline(void)
{
	if (g_status == SIGINT)
	{
		g_status = 128 + SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return (0);
}

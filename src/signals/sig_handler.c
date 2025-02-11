/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:41:24 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/11 15:54:29 by ipersids         ###   ########.fr       */
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
	{
		g_status = sig;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @brief Signal SIGINT handler for the heredoc child process.
 * 
 * @param sig The signal number. 
 */
void	sig_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_status = sig;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

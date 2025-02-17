/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_interceptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:34:07 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/17 09:29:08 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static void	sig_init(void (*sint_handler)(int), void (*squit_handler)(int));
static int	sig_struct_init(struct sigaction *sa, int signo);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Sets up signal handlers based on the specified mode.
 * 
 * This function sets up signal handlers for SIGINT and SIGQUIT 
 * based on the specified modes of the shell.
 * 
 * @param mode The signal mode (interactive, heredoc, default, or ignore).
 */
void	sig_interceptor(t_sig_mode mode)
{
	if (mode == SIG_INTERACTIVE_MODE)
		sig_init(sig_sigint_main, SIG_IGN);
	else if (mode == SIG_HEREDOC_MODE)
		sig_init(sig_sigint_main, SIG_IGN);
	else
		sig_init(SIG_DFL, SIG_DFL);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Initializes the signal handlers for SIGINT and SIGQUIT.
 * 
 * @param sint_handler The signal handler for SIGINT.
 * @param squit_handler The signal handler for SIGQUIT.
 */
static void	sig_init(void (*sint_handler)(int), void (*squit_handler)(int))
{
	struct sigaction	sint;
	struct sigaction	squit;

	sint.sa_handler = sint_handler;
	squit.sa_handler = squit_handler;
	if (sig_struct_init(&sint, SIGINT) == -1)
		exit(ERROR_GENERIC);
	if (sig_struct_init(&squit, SIGQUIT) == -1)
		exit(ERROR_GENERIC);
}

/**
 * @brief Initializes the sigaction structure for a specific signal.
 * 
 * @param sa Pointer to the sigaction structure to initialize.
 * @param signo The signal number to initialize the sigaction structure for.
 * @return int Returns 0 on success, or an error code on failure.
 */
static int	sig_struct_init(struct sigaction *sa, int signo)
{
	sa->sa_flags = SA_RESTART | SA_NOCLDSTOP;
	if (sigemptyset(&sa->sa_mask) == -1)
	{
		perror("minishell: sigemptyset");
		return (-1);
	}
	if (sigaction(signo, sa, NULL) == -1)
	{
		perror("minishell: sigaction");
		return (-1);
	}
	return (0);
}

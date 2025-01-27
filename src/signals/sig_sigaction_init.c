/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_sigaction_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:40:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/25 02:46:38 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the signal handlers using sigaction.
 * 
 * This function initializes the signal handlers for SIGINT and SIGQUIT 
 * using sigaction. It sets the provided handler function for these signals 
 * and configures the signal mask.
 * 
 * rl_catch_signals = 0;  Disable readline's default signal handling
 * 
 * @param sa Pointer to the sigaction structure.
 * @param handler Pointer to the signal handler function.
 */
void	sig_sigaction_init(struct sigaction *sa, \
							void (*handler) (int, siginfo_t *, void *))
{
	rl_catch_signals = 0;
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = handler;
	if (sigemptyset(&sa->sa_mask) == -1 \
		|| sigaddset(&sa->sa_mask, SIGINT) == -1 \
		|| sigaddset(&sa->sa_mask, SIGQUIT) == -1)
	{
		perror("minishell: sigemptyset or sigaddset failed");
		exit(ERROR_GENERIC);
	}
	if (sigaction(SIGINT, sa, NULL) == -1 \
		|| sigaction(SIGQUIT, sa, NULL) == -1)
	{
		perror("minishell: sigaction failed");
		exit(ERROR_GENERIC);
	}
}

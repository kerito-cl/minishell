/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_sigaction_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:40:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/23 13:21:38 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//rl_catch_signals = 0;  Disable readline's default signal handling
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
		exit(ERROR_SIGACTION_FAILS);
	}
	if (sigaction(SIGINT, sa, NULL) == -1 \
		|| sigaction(SIGQUIT, sa, NULL) == -1)
	{
		perror("minishell: sigaction failed");
		exit(ERROR_SIGACTION_FAILS);
	}
}

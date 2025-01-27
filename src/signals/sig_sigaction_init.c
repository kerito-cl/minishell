/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_sigaction_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:40:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/15 08:28:04 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		perror(strerror(errno));
		exit(ERROR_SIGACTION_FAILS);
	}
	if (sigaction(SIGINT, sa, NULL) == -1 \
		|| sigaction(SIGQUIT, sa, NULL) == -1)
	{
		perror(strerror(errno));
		exit(ERROR_SIGACTION_FAILS);
	}
}

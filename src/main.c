/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:37:16 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/15 08:34:44 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_status = 0;

int	main(void)
{
	struct sigaction	sa;
	char				*line;

	sig_sigaction_init(&sa, sig_handler_main);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		add_history(line);
		free(line);
	}
	rl_clear_history();
	free(line);
	write(1, "Good luck!\n", 11);
	return (0);
}

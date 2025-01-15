/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:37:16 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/15 21:51:01 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*line;
	t_env				env;

	if (argc != 1 || !argv || !envp)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	env_init(envp, &env);
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
	env_free(&env);
	write(1, "Good luck!\n", 11);
	return (0);
}

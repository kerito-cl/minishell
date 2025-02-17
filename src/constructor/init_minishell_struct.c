/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:36:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/18 01:25:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the minishell structure.
 * 
 * This function initializes the minishell structure by setting the exit code,
 * initializing the environment, and determining if the shell is running in
 * interactive mode.
 * 
 * rl_catch_signals = 0;  Disable readline's default signal handling.
 * 
 * @param ms Pointer to the minishell structure to initialize.
 * @param envp Array of environment variables.
 */
void	init_minishell_struct(t_mshell *ms, char **envp)
{
	rl_catch_signals = 0;
	sig_interceptor(SIG_INTERACTIVE_MODE);
	rl_event_hook = sig_reset_readline;
	ms->is_term_set = FALSE;
	init_termios_attributes(ms);
	ms->exit_code = init_environment(envp, &ms->env);
	if (ms->exit_code != 0)
	{
		ft_putstr_fd("minishell: env: initialisation fails\n", STDERR_FILENO);
		exit(ms->exit_code);
	}
	ms->input = NULL;
	ms->root = NULL;
	ms->tmp_node = NULL;
}

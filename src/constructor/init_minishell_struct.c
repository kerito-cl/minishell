/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:36:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/30 07:31:13 by ipersids         ###   ########.fr       */
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
 * @param ms Pointer to the minishell structure to initialize.
 * @param envp Array of environment variables.
 */
void	init_minishell_struct(t_mshell *ms, char **envp)
{
	ms->exit_code = init_environment(envp, &ms->env);
	if (ms->exit_code != 0)
	{
		ft_putstr_fd("minishell: env: initialisation fails\n", STDERR_FILENO);
		exit(ms->exit_code);
	}
	ms->interactive_mode = isatty(STDIN_FILENO);
	ms->input = NULL;
	ms->root = NULL;
	ms->tmp_node = NULL;
}

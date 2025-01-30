/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_destroy_minishell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:01:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/30 07:35:43 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all resources and exits the minishell program.
 * 
 * This function is responsible for cleaning up and releasing all allocated
 * resources before terminating the minishell program.
 * 
 * @param ms A pointer to the minishell structure containing all necessary
 *           data and resources to be freed.
 */
void	exit_destroy_minishell(t_mshell *ms)
{
	if (ms->env.envp != NULL)
	{
		free_environment(&ms->env);
		ms->env.envp = NULL;
	}
	if (ms->root != NULL)
	{
		free_ast(ms->root);
		ms->root = NULL;
	}
	if (ms->input != NULL)
	{
		free(ms->input);
		ms->input = NULL;
	}
	rl_clear_history();
	exit(ms->exit_code);
}

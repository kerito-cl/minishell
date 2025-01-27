/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_destroy_minishell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:01:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 23:49:28 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_destroy_minishell(t_mshell *ms)
{
	if (ms->env.envp != NULL)
		free_environment(&ms->env);
	exit(ms->exit_code);
}

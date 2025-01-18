/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_destroy_minishell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:01:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/19 00:34:58 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_destroy_minishell(t_mshell *ms)
{
	if (ms->env.envp != NULL)
		env_free(&ms->env);
	exit(ms->exit_code);
}

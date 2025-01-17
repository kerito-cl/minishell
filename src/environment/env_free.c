/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:24:37 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/17 11:54:44 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the memory allocated for the environment variables.
 * 
 * This function frees the memory allocated for the environment variables
 * and sets the pointers to NULL. It also resets the length of the env array.
 * 
 * @param env Pointer to the environment struct containing an array of strings.
 */
void	env_free(t_env *env)
{
	unsigned int	i;

	if (!env || !env->envp)
		return ;
	i = 0;
	while (i < env->len)
	{
		free(env->envp[i]);
		env->envp[i] = NULL;
		i++;
	}
	free(env->envp);
	env->envp = NULL;
	env->len = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:09:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/17 11:57:35 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the environment structure with the given variables.
 * 
 * This function initializes the environment structure by copying 
 * the given environment variables into a dynamically allocated array. 
 * It also sets the initial capacity of the array.
 * 
 * @param envp_arr The array of environment variables.
 * @param env Pointer to the environment structure to initialize.
 * @return int Returns 0 on success, or an error code on failure.
 */
int	env_init(char **envp_arr, t_env *env)
{
	env->len = 0;
	while (envp_arr[env->len] != NULL)
		env->len++;
	env->capacity = env->len * 2;
	env->envp = (char **) ft_calloc(env->capacity, sizeof(char *));
	if (!env->envp)
	{
		perror("env: ");
		return (ERROR_MALLOC_FAILS);
	}
	env->len = 0;
	while (envp_arr[env->len] != NULL)
	{
		env->envp[env->len] = ft_strdup(envp_arr[env->len]);
		if (!env->envp[env->len])
		{
			env_free(env);
			perror("env: ");
			return (ERROR_MALLOC_FAILS);
		}
		env->len++;
	}
	return (0);
}

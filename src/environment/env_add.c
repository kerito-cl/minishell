/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:20:10 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/10 14:20:51 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static char	**realloc_env(t_env *env);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Adds or updates an environment variable in the environment struct.
 * 
 * This function adds a new environment variable or updates an existing one.
 * If the environment array is full, it reallocates memory.
 * 
 * @param var The variable to add or update in the environment.
 * @param env Pointer to the environment struct containing an array of strings.
 * @return int Returns 0 on success, or an error code on failure.
 */
int	env_add(const char *var, t_env *env)
{
	size_t	i;
	char	*tmp;

	tmp = NULL;
	if (env->len + 1 >= env->capacity)
	{
		if (!realloc_env(env))
			return (ERROR_MALLOC_FAILS);
	}
	tmp = ft_strdup(var);
	if (!tmp)
	{
		perror("minishell: malloc");
		return (ERROR_MALLOC_FAILS);
	}
	i = 0;
	if (env_find_variable(var, env, &i) != NULL)
	{
		free(env->envp[i]);
		env->envp[i] = tmp;
		return (0);
	}
	env->envp[env->len] = tmp;
	env->len += 1;
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Reallocate memory for the array of environment variables.
 * 
 * This function doubles the capacity of the environment array 
 * and copies the existing environment variables to the new array.
 * It will free original environment array only in case of success.
 * 
 * @param env Pointer to the environment struct containing an array of strings.
 * @return char** Pointer to the newly allocated environment structure, 
 * 				  or NULL on failure.
 */
static char	**realloc_env(t_env *env)
{
	char			**res;
	unsigned int	new_capacity;
	unsigned int	i;

	new_capacity = env->capacity * 2;
	res = (char **) ft_calloc(new_capacity, sizeof(char *));
	if (!res)
	{
		perror("minishell: ft_calloc");
		return (NULL);
	}
	i = 0;
	while (i < env->len)
	{
		res[i] = env->envp[i];
		i++;
	}
	free(env->envp);
	env->envp = res;
	env->capacity = new_capacity;
	return (env->envp);
}

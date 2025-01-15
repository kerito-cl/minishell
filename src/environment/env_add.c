/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:20:10 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/15 22:44:10 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**realloc_env(t_env *env);

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
		return (ERROR_MALLOC_FAILS);
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

static char	**realloc_env(t_env *env)
{
	char			**res;
	unsigned int	new_capacity;
	unsigned int	i;

	new_capacity = env->capacity * 2;
	res = (char **) ft_calloc(new_capacity, sizeof(char *));
	if (!res)
		return (NULL);
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

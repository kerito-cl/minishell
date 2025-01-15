/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:53:06 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/15 23:09:22 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_remove(const char *var, t_env *env)
{
	size_t			i;
	unsigned int	j;

	i = 0;
	if (env_find_variable(var, env, &i) == NULL)
		return (0);
	free(env->envp[i]);
	env->envp[i] = NULL;
	j = i + 1;
	while (j < env->len)
	{
		env->envp[i] = env->envp[j];
		i++;
		j++;
	}
	env->envp[i] = NULL;
	env->len = i;
	return (0);
}

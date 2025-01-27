/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_value_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:04:55 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/27 18:36:01 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns a constant pointer to the value of an environment variable.
 * 
 * This function takes the variable name in the format $NAME or NAME. 
 * It does not handle quotes and does not remove them. The resulting value 
 * cannot be modified (protected as a constant).
 * 
 * @param var The variable to search for in the environment.
 * @param env Pointer to the environment struct containing an array of strings.
 * @return const char* Pointer to the value string, 
 * 					   or NULL if the variable is not found.
 */
const char	*env_find_value_v2(const char *var, t_env *env)
{
	size_t	i;
	size_t	counter;
	char	*res;

	i = 0;
	counter = 0;
	if (!var || !env || ! env->envp)
		return (NULL);
	while (var[i])
	{
		if (var[i] == '$')
			counter++;
		i++;
	}
	res = (char **)malloc(sizeof(char *) * (counter + 1));
	if (!res)
		return (NULL);
	res[counter] = NULL;
	i = 0;
	while (i < counter)
	{
		while(*var != '$')
			var++;
		while (*var)
		{
			if (*var == '$')
			{
				var++;
				break;
			}
		}
		i++;
	}
	if (!env_find_variable_v2(var, env, &i))
		return (NULL);
	res = ft_strchr(env->envp[i], '=');
	if (res)
		return (++res);
	res = ft_memchr(env->envp[i], '\0', ft_strlen(env->envp[i]) + 1);
	return (res);
}

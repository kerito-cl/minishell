/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:04:55 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/20 16:41:14 by ipersids         ###   ########.fr       */
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
const char	*env_find_value(const char *var, t_env *env)
{
	size_t	i;
	char	*res;

	if (!var || !env || ! env->envp)
		return (NULL);
	if (*var == '$')
		var++;
	i = 0;
	if (!env_find_variable(var, env, &i))
		return (NULL);
	res = ft_strchr(env->envp[i], '=');
	if (res)
		return (++res);
	res = ft_memchr(env->envp[i], '\0', ft_strlen(env->envp[i]) + 1);
	return (res);
}

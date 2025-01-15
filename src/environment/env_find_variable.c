/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/15 22:44:38 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	strlen_until_char(const char *s, const char ch);

char	*env_find_variable(const char *var, t_env *env, size_t *i)
{
	size_t	len_var;
	size_t	len_env;

	if (!var || !env || !env->envp || !i)
		return (NULL);
	*i = 0;
	while (env->envp[*i] != NULL)
	{
		len_env = strlen_until_char(env->envp[*i], '=');
		len_var = strlen_until_char(var, '=');
		if (len_var == len_env && ft_strncmp(env->envp[*i], var, len_env) == 0)
			return (env->envp[*i]);
		*i += 1;
	}
	return (NULL);
}

static size_t	strlen_until_char(const char *s, const char ch)
{
	size_t	len;

	len = 0;
	while (*s != '\0' && *s != ch)
	{
		len++;
		s++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_variable_v2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:18 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/28 20:11:55 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static size_t	strlen_until_char(const char *s, const char ch);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Finds an environment variable in the environment array.
 * 
 * @param var The variable to search for in the environment.
 * @param env Pointer to the environment struct containing an array of strings.
 * @param i Pointer to a variable to store the index of the found variable.
 * @return char* Pointer to the found variable string, or NULL if not found.
 */

char	*env_find_variable_v2(const char *var, t_env *env, size_t *i)
{
	size_t	len_var;
	size_t	len_env;

	if (!var || !env || !env->envp || !i)
		return (NULL);
	*i = 0;
	len_var = strlen_until_char(var, 0);
	while (env->envp[*i] != NULL)
	{
		len_env = strlen_until_char(env->envp[*i], '=');
		if (len_var == len_env && ft_strncmp(env->envp[*i], var, len_env) == 0)
			return (env->envp[*i]);
		*i += 1;
	}
	return (NULL);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Calculates the length of a string until a specified character.
 * 
 * @param s The input string.
 * @param ch The character to stop at.
 * @return size_t The length of the string until the specified character.
 */
static size_t	strlen_until_char(const char *s, const char ch)
{
	size_t	len;

	len = 0;
    while (*s != '\0' && !ft_strchr(" \"'<>|", *s) && *s != ch)
	{
		len++;
		s++;
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:33:05 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/17 14:11:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the env command.
 * 
 * This function mimics the behavior of the env command. It prints the current
 * environment variables to the standard output.
 * 
 * @param args Array of arguments passed to the env command.
 * @param env Pointer to the environment struct containing an array of strings.
 * @return int Returns 0 on success, or an error code if arguments 
 * 			   or options are provided.
 */
int	builtin_env(char **args, t_env *env)
{
	unsigned int	i;

	if (!args || args[0] != NULL)
	{
		ft_putstr_fd("env: arguments or options are not supported\n", 2);
		return (ERROR_BUILTIN_ENV_ARGS);
	}
	i = 0;
	while (i < env->len)
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:33:05 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 23:18:46 by ipersids         ###   ########.fr       */
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
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd("options or arguments are not supported\n", STDERR_FILENO);
		return (ERROR_GENERIC);
	}
	i = 0;
	while (i < env->len)
	{
		if (ft_strchr(env->envp[i], '='))
			printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}

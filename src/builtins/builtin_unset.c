/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:06:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/18 17:56:46 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes each variable name.
 * 
 * This function mimics the behavior of the unset command. It removes 
 * environment variables. If an invalid variable name is provided, it prints
 * an error message and returns an error code.
 * 
 * @param args Array of arguments passed to the unset command.
 * @param env Pointer to the environment struct containing an array of strings.
 * @return int Returns 0 on success, or an error code if an invalid variable 
 * 			   name is provided.
 */
int	builtin_unset(char **args, t_env *env)
{
	size_t	i;
	int		exit_code;

	exit_code = 0;
	if (!args || args[0] == NULL)
		return (exit_code);
	i = 0;
	while (args[i] != NULL)
	{
		if (!builtin_is_identifier_valid(args[i]) || ft_strchr(args[i], '='))
		{
			printf("minishell: unset: '%s': ", args[i]);
			printf("not a valid identifier\n");
			exit_code = ERROR_BUILTIN_UNSET_INV_VAR;
		}
		else
			exit_code = env_remove(args[i], env);
		i++;
	}
	return (exit_code);
}

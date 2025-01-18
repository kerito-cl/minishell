/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:06:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/18 17:42:54 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		builtin_unset(char **args, t_env *env)
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

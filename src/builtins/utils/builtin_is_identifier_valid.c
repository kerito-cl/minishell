/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_is_identifier_valid.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:49:14 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/15 04:53:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given variable name (identifier) is valid.
 * 
 * Allowed characters: letters (`a-z`, `A-Z`), digits (`0-9`) 
 * and underscore (`_`). Variable names cannot start with a digit or be empty.
 * 
 * @param var The variable name (identifier) to check.
 * @return int Returns 1 if the variable name is valid, 0 otherwise.
 */
int	builtin_is_identifier_valid(const char *var)
{
	size_t	i;

	if (!var || ft_isdigit(var[0]) || var[0] == '\0')
		return (0);
	i = 0;
	if (var[0] == '=')
		return (0);
	while (var[i] != '\0' && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

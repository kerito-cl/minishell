/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:06:23 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 23:24:11 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	unset_error_check(char *arg, int i);

/* --------------------------- Public Functions ---------------------------- */

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
		exit_code = unset_error_check(args[i], i);
		if (i == 0 && exit_code == ERROR_INVALID_OPTION)
			return (exit_code);
		if (exit_code == 0)
			exit_code = env_remove(args[i], env);
		i++;
	}
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Checks for errors in the unset command arguments.
 * 
 * @param arg The argument to check.
 * @param i The index of the argument in the args array.
 * @return int Returns 0 if no error, or an error code if an invalid option 
 * 			   or identifier is found.
 */
static int	unset_error_check(char *arg, int i)
{
	if (i == 0 && arg[0] == '-')
	{
		ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': options are not supperted\n", STDERR_FILENO);
		ft_putstr_fd("unset: usage: unset [name ...]\n", STDERR_FILENO);
		return (ERROR_INVALID_OPTION);
	}
	if (!builtin_is_identifier_valid(arg) || ft_strchr(arg, '='))
	{
		ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (ERROR_GENERIC);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:58:44 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 22:32:49 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static t_bool	is_exit_code_valid(const char *str, int *exit_code);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Executes the exit command.
 * 
 * The exit status of an executed command is the value returned by the waitpid 
 * system call or equivalent function. Exit statuses fall between 0 and 255, 
 * though, as explained below, the shell may use values above 125 specially. 
 * Exit statuses from shell builtins and compound commands are also limited 
 * to this range. Under certain circumstances, the shell will use special 
 * values to indicate specific failure modes.
 * 
 * 1) If no arguments are provided, the shell exits with the exit status 
 * of the last executed command.
 *
 * 2) If one numeric argument is provided, the shell exits with that status.
 * 
 * 3) If multiple arguments are provided, the shell should display an error 
 * and not exit.
 * 
 * @param args Array of arguments passed to the exit command.
 * @param ms Pointer to the minishell structure.
 * @return int Returns the exit code.
 */
int	builtin_exit(char **args, t_mshell *ms)
{
	int	len;

	len = 0;
	while (args && args[len])
		len++;
	if (len > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		ms->exit_code = ERROR_GENERIC;
		return (ms->exit_code);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[0] != NULL && !is_exit_code_valid(args[0], &ms->exit_code))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	exit_destroy_minishell(ms);
	return (ms->exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Checks if the given exit code is valid.
 * 
 * @param str The string representing the exit code.
 * @param exit_code Pointer to an integer to store the parsed exit code.
 * @return t_bool Returns TRUE if the exit code is valid, FALSE otherwise.
 */
static t_bool	is_exit_code_valid(const char *str, int *exit_code)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(str[i]))
		{
			*exit_code = ERROR_INVALID_EXIT_CODE;
			return (FALSE);
		}
		i++;
	}
	*exit_code = ft_abc(ft_atol(str) % 255);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:01:49 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/23 18:21:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	is_n_option(const char *word);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Executes the echo command.
 * 
 * This function mimics the behavior of the echo command. It prints the 
 * given arguments to the standard output. If the -n option is provided, 
 * it does not print the trailing newline. 
 * 
 * @note it doesn't check any special symbols for now.
 * 
 * @param args Array of arguments passed to the echo command.
 * @return int Returns 0 on success.
 */
int	builtin_echo(char **args)
{
	int	is_new_line;
	int	i;

	i = 0;
	is_new_line = 1;
	while (args[i] && is_n_option(args[i]))
	{
		is_new_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (is_new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Checks if the given word is the -n option.
 * 
 * @param word The word to check.
 * @return int Returns 1 if the word is the -n option, 0 otherwise.
 */
static int	is_n_option(const char *word)
{
	return (word && word[0] == '-' && word[1] == 'n' && word[2] == '\0');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:52:52 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/18 18:31:27 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the absolute pathname of the current working directory.
 * 
 * This function mimics the behavior of the pwd command. It prints the absolute
 * pathname of the current working directory. If any arguments or options 
 * are provided, it prints an error message and returns an error code.
 * 
 * @param args Array of arguments passed to the pwd command.
 * @param env Pointer to the environment structure (not used in this function).
 * @return int Returns 0 on success, or an error code if arguments 
 * 			   or options are provided.
 */
int	builtin_pwd(char **args)
{
	char	*buf;

	if (args && args[0] != NULL)
	{
		printf("minishell: pwd: options and arguments aren't supported\n");
		printf("pwd: usage: pwd\n");
		return (ERROR_BUILTIN_PWD_ARGS);
	}
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		perror("getcwd: ");
		return (ERROR_BUILTIN_GETCWD_FAILS);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

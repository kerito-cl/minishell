/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/17 13:15:16 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef COLORS
# define COLORS
# 	define RED "\033[0;31m"
# 	define GREEN "\033[0;32m"
# 	define PURPLE "\033[0;35m"
# 	define DEFAULT "\033[0m"
#endif

static void	test_echo(char *str);

void test_builtin(void) {
	
	printf("\n\n%s-------------- TEST ECHO --------------%s\n\n", PURPLE, DEFAULT);
	
	test_echo("just a string without options '-n'");
	test_echo("-n just a string with only on option '-n'");
	test_echo("-n -n -n just a string with a few '-n'");
	test_echo("-n -n -n-n just a string with a few '-n' and some wrong options");
	test_echo("- -n -n-n just a string with a wrong option at the start");
	test_echo("just a string with a back slash things \\avvv \\n\'");
}

static void	test_echo(char *str) {
	char **arr = NULL;

	printf("%sTest string:%s %s\n", GREEN, DEFAULT, str);
	arr = ft_split(str, ' ');
	if (!arr)
	{
		perror(strerror(errno));
		return ;
	}
	printf("%sstart >>>%s\n", RED, DEFAULT);
	builtin_echo(arr);
	printf("%s<<< end%s\n\n",  RED, DEFAULT);
	free(arr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_dollar_expansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:37:42 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/15 14:06:09 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static char	*exchange_variable(char *str, int fd, t_env *env);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Handles dollar variable expansion in the input string.
 * 
 * This function processes the input string and replaces occurrences
 * of dollar variables with their corresponding values from the environment.
 * It writes the expanded input to the specified file descriptor.
 * 
 * @param input The input string containing dollar variables.
 * @param fd_write The file descriptor to write the expanded input to.
 * @param ms The minishell context.
 */
void	exe_handle_dollar_expansion(char *input, int fd_write, t_mshell *ms)
{
	char	*start;

	start = input;
	while (*start != '\0')
	{
		if (*start == '$' && (ft_isdigit(*(start + 1)) || *(start + 1) == '?'))
		{
			if (*(start + 1) == '?')
				ft_putnbr_fd(ms->exit_code, fd_write);
			start += 2;
			continue ;
		}
		if (*start == '$' && (ft_isalnum(*(start + 1)) || *(start + 1) == '_'))
		{
			start = exchange_variable(start + 1, fd_write, &ms->env);
			continue ;
		}
		write(fd_write, start, 1);
		start++;
	}
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Replaces a variable in the input with its value from the environment.
 * 
 * @param str The input string containing the variable name.
 * @param fd The file descriptor to write the variable value to.
 * @param env The environment containing variable values.
 * @return char* The pointer to the next char in the input after the var.name.
 */
static char	*exchange_variable(char *str, int fd, t_env *env)
{
	int			i;
	char		tmp;
	const char	*var;

	var = NULL;
	tmp = '\0';
	i = 0;
	while (str[i] != '\0' && (ft_isalnum(*(str + i)) || str[i] == '_'))
		i++;
	tmp = str[i];
	str[i] = '\0';
	var = env_find_value(str, env);
	str[i] = tmp;
	if (var)
		write(fd, var, ft_strlen(var));
	return (str + i);
}

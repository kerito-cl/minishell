/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_dollar_expansion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:37:42 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/14 01:07:19 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*exchange_variable(char *str, int fd, t_env *env);

void	exe_handle_dollar_expansion(char *input, int fd_write, t_env *env)
{
	char	*start;

	start = input;
	while (*start != '\0')
	{
		if (*start == '$' && ft_isdigit(*(start + 1)))
		{
			start += 2;
			continue ;
		}
		if (*start == '$' && (ft_isalnum(*(start + 1)) || *(start + 1) == '_'))
		{
			start = exchange_variable(start + 1, fd_write, env);
			continue ;
		}
		write(fd_write, start, 1);
		start++;
	}
}

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

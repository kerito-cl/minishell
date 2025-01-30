/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_check_special_case.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 06:09:43 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/30 06:25:47 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_check_special_case(char **args, t_mshell *ms)
{
	char		*tmp;
	int			i;

	if (!args || !args[0])
		return (0);
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], EXIT_CODE_CASE) == 0)
		{
			tmp = ft_itoa(ms->exit_code % 255);
			if (!tmp)
			{
				perror("minishell: malloc");
				return (errno);
			}
			free(args[i]);
			args[i] = tmp;
		}
		i++;
	}
	return (0);
}

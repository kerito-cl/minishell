/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_wait_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:27:47 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/21 19:56:12 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_wait_children(pid_t *pids, int amount)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < amount)
	{
		if (waitpid(pids[i], &exit_code, 0) == -1)
		{
			perror("minishell: waitpid");
			return (errno);
		}
		i++;
	}
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (EXIT_FAILURE);
}

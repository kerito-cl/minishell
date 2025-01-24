/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_wait_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:27:47 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 14:37:14 by ipersids         ###   ########.fr       */
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
	if (WIFSIGNALED(exit_code))
	{
		ft_putstr_fd("minishell: process terminated by signal ", STDERR_FILENO);
		ft_putnbr_fd(WTERMSIG(exit_code), STDERR_FILENO);
		ft_putnbr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (EXIT_FAILURE);
}

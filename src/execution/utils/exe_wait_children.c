/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_wait_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:27:47 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/25 00:23:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Waits for all child processes to finish execution.
 * 
 * This function takes an array of process IDs (pids) and the number 
 * of processes (amount), and waits for each child process to complete. 
 * It returns the exit status of the last child process that terminates.
 * 
 * @param pids An array of process IDs representing the child processes.
 * @param amount The number of child processes.
 * @return int The exit status of the last child process that terminates.
 */
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
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (EXIT_FAILURE);
}

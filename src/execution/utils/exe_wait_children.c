/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_wait_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:27:47 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/15 23:49:07 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static void	display_message(int signo);

/* --------------------------- Public Functions ---------------------------- */

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
			if (errno == EINTR)
				continue ;
			return (perror("minishell: waitpid"), errno);
		}
		i++;
		g_status = 0;
	}
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	if (WIFSIGNALED(exit_code))
	{
		exit_code = WTERMSIG(exit_code);
		display_message(exit_code);
		return (exit_code + 128);
	}
	return (EXIT_FAILURE);
}

/* ------------------- Private Function Implementation --------------------- */

static void	display_message(int signo)
{
	if (signo == SIGINT)
	{
		g_status = 0;
		write(STDERR_FILENO, "\n", 1);
		return ;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (signo == SIGABRT)
		ft_putstr_fd("Abort signal from abort(3)\n", STDERR_FILENO);
	else if (signo == SIGBUS)
		ft_putstr_fd("Bus error (bad memory access)\n", STDERR_FILENO);
	else if (signo == SIGKILL)
		ft_putstr_fd("Kill signal\n", STDERR_FILENO);
	else if (signo == SIGPIPE)
		;
	else if (signo == SIGQUIT)
		ft_putstr_fd("Quit from keyboard\n", STDERR_FILENO);
	else if (signo == SIGSEGV)
		ft_putstr_fd("Segmentation fault: Invalid memory reference\n", 2);
	else
	{
		ft_putstr_fd("Process terminated by signal: ", STDERR_FILENO);
		ft_putnbr_fd(signo, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

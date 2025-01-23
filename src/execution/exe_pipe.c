/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:44:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/23 16:04:19 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_left_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms);
static int	run_right_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms);

/// Creating a pipe between two child processes
/// @todo Signals for child processes
int	exe_pipe(t_ast *root, t_mshell *ms)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (errno);
	}
	pid[0] = 0;
	pid[1] = 0;
	ms->exit_code = run_left_fork(pipe_fd, &pid[0], root->left, ms);
	if (ms->exit_code == 0)
		ms->exit_code = run_right_fork(pipe_fd, &pid[1], root->right, ms);
	ms->exit_code = exe_wait_children(pid, 2);
	return (ms->exit_code);
}

static int	run_left_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("minishell: fork");
		return (errno);
	}
	if (*pid == 0)
	{
		sig_child_process_handler(ms->interactive_mode);
		exe_close_fd(&pipe_fd[FD_READ]);
		if (dup2(pipe_fd[FD_WRITE], STDOUT_FILENO) == -1)
		{
			exe_close_fd(&pipe_fd[FD_WRITE]);
			exit(errno);
		}
		exe_close_fd(&pipe_fd[FD_WRITE]);
		ms->exit_code = exe_ast_tree(node, ms);
		exit(ms->exit_code);
	}
	exe_close_fd(&pipe_fd[FD_WRITE]);
	return (0);
}

static int	run_right_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("minishell: fork");
		return (errno);
	}
	if (*pid == 0)
	{
		sig_child_process_handler(ms->interactive_mode);
		exe_close_fd(&pipe_fd[FD_WRITE]);
		if (dup2(pipe_fd[FD_READ], STDIN_FILENO) == -1)
		{
			exe_close_fd(&pipe_fd[FD_READ]);
			exit(errno);
		}
		exe_close_fd(&pipe_fd[FD_READ]);
		ms->exit_code = exe_ast_tree(node, ms);
		exit(ms->exit_code);
	}
	exe_close_fd(&pipe_fd[FD_READ]);
	return (0);
}

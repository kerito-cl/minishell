/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:44:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/29 11:10:29 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	run_left_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms);
static int	run_right_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Executes a pipe command.
 * 
 * This function sets up a pipe between two commands represented 
 * by the left and right children of the AST node. It creates a pipe, 
 * forks two child processes to run the left and right commands, and waits 
 * for both children to finish.
 * 
 * @param root Pointer to the AST node representing the pipe command.
 * @param ms Pointer to the minishell structure containing the shell state.
 * @return int Returns 0 on success, or an error code on failure.
 */
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
	return (ms->exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Runs the left command in a forked child process.
 * 
 * This function forks a child process to run the left command of the pipe. 
 * It sets up the pipe for writing and executes the left command.
 * 
 * @param pipe_fd Array of file descriptors for the pipe.
 * @param pid Pointer to the process ID of the forked child process.
 * @param node Pointer to the AST node representing the left command.
 * @param ms Pointer to the minishell structure containing the shell state.
 * @return int Returns 0 on success, or an error code on failure.
 */
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
		sig_child_process_handler(SIG_DEFAULT_MODE);
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
	ms->exit_code = exe_wait_children(pid, 1);
	return (ms->exit_code);
}

/**
 * @brief Runs the right command in a forked child process.
 * 
 * This function forks a child process to run the right command of the pipe. 
 * It sets up the pipe for reading and executes the right command.
 * 
 * @param pipe_fd Array of file descriptors for the pipe.
 * @param pid Pointer to the process ID of the forked child process.
 * @param node Pointer to the AST node representing the right command.
 * @param ms Pointer to the minishell structure containing the shell state.
 * @return int Returns 0 on success, or an error code on failure.
 */
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
		sig_child_process_handler(SIG_DEFAULT_MODE);
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
	ms->exit_code = exe_wait_children(pid, 1);
	return (ms->exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:44:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/15 17:27:06 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	run_left_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms);
static int	run_right_fork(int pipe_fd[2], int *pid, t_ast *node, t_mshell *ms);
static void	handle_pipe(int pipe_fd[2], t_mshell *ms, int fd_close, int fd_dup);

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
	ms->exit_code = run_right_fork(pipe_fd, &pid[1], root->right, ms);
	ms->exit_code = exe_wait_children(pid, 2);
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
		ms->tmp_node = node;
		handle_pipe(pipe_fd, ms, FD_READ, FD_WRITE);
	}
	exe_close_fd(&pipe_fd[FD_WRITE]);
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
		ms->tmp_node = node;
		ms->exit_code = 0;
		handle_pipe(pipe_fd, ms, FD_WRITE, FD_READ);
	}
	return (ms->exit_code);
}

static void	handle_pipe(int pipe_fd[2], t_mshell *ms, int fd_close, int fd_dup)
{
	int	new_fd;

	new_fd = STDOUT_FILENO;
	if (fd_dup == FD_READ)
		new_fd = STDIN_FILENO;
	sig_interceptor(SIG_DEFAULT_MODE);
	exe_close_fd(&pipe_fd[fd_close]);
	if (dup2(pipe_fd[fd_dup], new_fd) == -1)
	{
		exe_close_fd(&pipe_fd[fd_dup]);
		perror("minishell: dup2");
		exit(errno);
	}
	exe_close_fd(&pipe_fd[fd_dup]);
	ms->exit_code = exe_ast_tree(ms->tmp_node, ms);
	exit(ms->exit_code);
}

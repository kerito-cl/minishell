/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:44:20 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/21 19:59:53 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_left_fork(int pipe_fd[2], int *pid, t_ast *node);
static int	create_right_fork(int pipe_fd[2], int *pid, t_ast *node);

int	exe_pipe(t_ast *root, t_mshell *ms)
{
	int		exit_code;
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (errno);
	}
	exit_code = create_left_fork(&pipe_fd, &pid[0], root->left);
	if (exit_code == 0)
		exit_code = create_right_fork(&pipe_fd, &pid[1], root->left)
	exe_wait_children(pid, 2);
}

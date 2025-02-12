/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:12:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/12 19:19:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_heredoc_prompt(t_mshell *ms, int fd_write, char *input);

int	exe_heredoc(t_ast *node, t_mshell *ms)
{
	pid_t		pid;
	int			fd;
	char 		*input;

	pid = fork();
	input = NULL;
	if (pid == 0)
	{
		sig_interceptor(SIG_HEREDOC_MODE);
		fd = open(HEREDOC_NAME, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("minishell: open");
			exit(errno);
		}
		ms->tmp_node = node;
		ms->exit_code = run_heredoc_prompt(ms, fd, input);
		close(fd);
		fd = open(HEREDOC_NAME, O_RDONLY);
		if (fd < 0)
		{
			perror("minishell: open");
			exit(errno);
		}
		if (unlink(HEREDOC_NAME) == -1)
		{
			perror("minishell: unlink");
			exit(errno);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			exit(errno);
		}
		ms->exit_code = exe_ast_tree(ms->tmp_node->right, ms);
		// ms->exit_code = exe_ast_tree(ms->tmp_node->left, ms);
		exit(ms->exit_code);
	}
	ms->exit_code = exe_wait_children(&pid, 1);
	unlink(HEREDOC_NAME);
	return (ms->exit_code);
}

// static int	run_left_fork(int doc_fd[2], int *pid, t_ast *node, t_mshell *ms);
// static int	run_heredoc_prompt(t_ast *node, int fd_write, char *input, t_mshell *ms);
// static int	run_right_fork(int doc_fd[2], int *pid, t_ast *node, t_mshell *ms);

// int	exe_heredoc(t_ast *node, t_mshell *ms)
// {
// 	int		doc_fd[2];
// 	pid_t	pid[2];

// 	if (pipe(doc_fd) == -1)
// 	{
// 		perror("minishell: pipe");
// 		return (errno);
// 	}
// 	pid[0] = 0;
// 	pid[1] = 0;
// 	ms->exit_code = run_left_fork(doc_fd, &pid[0], node, ms);
// 	ms->exit_code = exe_wait_children(&pid[0], 1);
// 	if (ms->exit_code == 0)
// 		ms->exit_code = run_right_fork(doc_fd, &pid[1], node, ms);
// 	return (ms->exit_code);
// }

// static int	run_left_fork(int doc_fd[2], int *pid, t_ast *node, t_mshell *ms)
// {
// 	char	*input;

// 	input = NULL;
// 	*pid = fork();
// 	if (*pid == -1)
// 	{
// 		perror("minishell: fork");
// 		return (errno);
// 	}
// 	if (*pid == 0)
// 	{
// 		sig_interceptor(SIG_HEREDOC_MODE);
// 		exe_close_fd(&doc_fd[FD_READ]);
// 		while (TRUE)
// 		{
// 			ms->exit_code = run_heredoc_prompt(node, doc_fd[FD_WRITE], input);
// 			if (!ms->exit_code)
// 				break ;
// 		}
// 		ms->exit_code = exe_ast_tree(node->left, ms);
// 		exe_close_fd(&doc_fd[FD_WRITE]);
// 		exit(ms->exit_code);
// 	}
// 	exe_close_fd(&doc_fd[FD_WRITE]);
// 	return (0);
// }

static int	run_heredoc_prompt(t_mshell *ms, int fd_write, char *input)
{
	while (TRUE)
	{
		if (g_status == SIGINT)
		{
			g_status = 0;
			unlink(HEREDOC_NAME);
			close(fd_write);
			exit(ERROR_INTERUPTED_SIGINT);
		}
		input = readline("> ");
		if (!input)
			return (0);
		if (ft_strcmp(input, ms->tmp_node->value[0]) == 0)
		{
			free(input);
			if (ms->tmp_node->left != NULL && ms->tmp_node->left->type == REIN2)
			{
				ms->tmp_node = ms->tmp_node->left;
				continue ;
			}
			else
				break ;
		}
		write(fd_write, input, ft_strlen(input));
		write(fd_write, "\n", 1);
		free(input);
	}
	return (0);
}

// static int	run_right_fork(int doc_fd[2], int *pid, t_ast *node, t_mshell *ms)
// {
// 	*pid = fork();
// 	if (*pid == -1)
// 	{
// 		perror("minishell: fork");
// 		return (errno);
// 	}
// 	if (*pid == 0)
// 	{
// 		sig_interceptor(SIG_DEFAULT_MODE);
// 		exe_close_fd(&doc_fd[FD_WRITE]);
// 		if (dup2(doc_fd[FD_READ], STDIN_FILENO) == -1)
// 		{
// 			exe_close_fd(&doc_fd[FD_READ]);
// 			exit(errno);
// 		}
// 		exe_close_fd(&doc_fd[FD_READ]);
// 		ms->exit_code = exe_ast_tree(node->right, ms);
// 		exit(ms->exit_code);
// 	}
// 	exe_close_fd(&doc_fd[FD_READ]);
// 	ms->exit_code = exe_wait_children(pid, 1);
// 	return (ms->exit_code);
// }

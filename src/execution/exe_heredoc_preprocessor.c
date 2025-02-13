/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc_preprocessor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:12:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/13 23:38:06 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exe_heredoc(t_ast *node, t_mshell *ms);
static void	handle_heredoc_fork(t_ast *node, int doc_fd[2]);
static int	run_heredoc_prompt(t_ast *node, int fd_write);

int exe_heredoc_preprocessor(t_ast *node, t_mshell *ms)
{
	int	exit_code;

	exit_code = 0;
    if (node == NULL)
        return (exit_code);
	if (node->type == REIN2 && (!node->value || !node->value[0]))
	{
		ft_putstr_fd("minishell: syntax error ", STDERR_FILENO);
		ft_putstr_fd("near unexpected token `newline'\n", STDERR_FILENO);
		ms->exit_code = ERROR_SYNTAX_HEREDOC;
		return (ERROR_SYNTAX_HEREDOC);
	}
    if (node->type == REIN2)
		exit_code = exe_heredoc(node, ms);
	if (exit_code != 0)
		return (exit_code);
	exit_code += exe_heredoc_preprocessor(node->left, ms);
	exit_code += exe_heredoc_preprocessor(node->right, ms);
	return (exit_code);
}

static int	exe_heredoc(t_ast *node, t_mshell *ms)
{
	int		doc_fd[2];
	pid_t	pid;

	if (pipe(doc_fd) == -1)
	{
		perror("minishell: heredoc: pipe");
		return (errno);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: heredoc: fork");
		return (errno);
	}
	if (pid == 0)
		handle_heredoc_fork(node, doc_fd);
	exe_close_fd(&doc_fd[FD_WRITE]);
	ms->exit_code = exe_wait_children(&pid, 1);
	if (ms->exit_code != 0)
	{
		exe_close_fd(&doc_fd[FD_READ]);
		return (ms->exit_code);
	}
	node->fd = doc_fd[FD_READ];
	return (EXIT_SUCCESS);
}

static void	handle_heredoc_fork(t_ast *node, int doc_fd[2])
{
	sig_interceptor(SIG_HEREDOC_MODE);
	exe_close_fd(&doc_fd[FD_READ]);
	run_heredoc_prompt(node, doc_fd[FD_WRITE]);
	exe_close_fd(&doc_fd[FD_WRITE]);
	exit(EXIT_SUCCESS);
}

static int	run_heredoc_prompt(t_ast *node, int fd_write)
{
	char	*input;

	input = NULL;
	while (TRUE)
	{
		if (g_status == SIGINT)
		{
			g_status = 0;
			close(fd_write);
			exit(ERROR_INTERUPTED_SIGINT);
		}
		input = readline("> ");
		if (!input)
			return (0);
		if (ft_strcmp(input, node->value[0]) == 0)
			break ;
		write(fd_write, input, ft_strlen(input));
		write(fd_write, "\n", 1);
		free(input);
	}
	free(input);
	return (0);
}

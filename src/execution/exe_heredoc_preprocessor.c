/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc_preprocessor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:12:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/14 11:38:05 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exe_heredoc(t_ast *node, t_mshell *ms);
static void	handle_heredoc_fork(t_ast *node, int doc_fd[2], t_mshell *ms);
static int	run_prompt(t_ast *node, int fd, t_bool is_dollar, t_env *env);

int exe_heredoc_preprocessor(t_ast *node, t_mshell *ms)
{
	int	exit_code;

	exit_code = 0;
    if (node == NULL)
        return (exit_code);
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
		handle_heredoc_fork(node, doc_fd, ms);
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

static void	handle_heredoc_fork(t_ast *node, int doc_fd[2], t_mshell *ms)
{
	sig_interceptor(SIG_HEREDOC_MODE);
	exe_close_fd(&doc_fd[FD_READ]);
	run_prompt(node, doc_fd[FD_WRITE], node->value[0][0] == '$', &ms->env);
	exe_close_fd(&doc_fd[FD_WRITE]);
	exit(EXIT_SUCCESS);
}

static int	run_prompt(t_ast *node, int fd, t_bool is_dollar, t_env *env)
{
	char	*input;

	input = NULL;
	while (TRUE)
	{
		if (g_status == SIGINT)
		{
			g_status = 0;
			close(fd);
			exit(ERROR_INTERUPTED_SIGINT);
		}
		input = readline("> ");
		if (!input)
			return (0);
		if (ft_strcmp(input, node->value[0]) == 0)
			break ;
		if (is_dollar)
			exe_handle_dollar_expansion(input, fd, env);
		else
			write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	return (0);
}

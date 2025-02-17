/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 08:27:57 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/17 09:55:37 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static void	handle_heredoc_fork(t_ast *node, int fd[2], t_mshell *ms);
static int	run_prompt(t_ast *node, int fd, t_bool is_dollar, t_mshell *ms);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Executes the heredoc for a given AST node.
 * 
 * @param node The current AST node.
 * @param ms The minishell context.
 * @return int The exit code of the heredoc execution.
 */
int	exe_heredoc(t_ast *node, t_mshell *ms)
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

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Handles the heredoc input in the child process.
 * 

 * 
 * @param node The current AST node.
 * @param fd The file descriptors for the pipe.
 * @param ms The minishell context.
 */
static void	handle_heredoc_fork(t_ast *node, int fd[2], t_mshell *ms)
{
	int	is_dollar;

	sig_interceptor(SIG_HEREDOC_MODE);
	exe_close_fd(&fd[FD_READ]);
	is_dollar = ft_strchr(node->value[0], '$') != NULL;
	ms->exit_code = 0;
	rl_event_hook = sig_reset_heredoc_readline;
	run_prompt(node, fd[FD_WRITE], is_dollar, ms);
	exe_close_fd(&fd[FD_WRITE]);
	exit(ms->exit_code);
}

/**
 * @brief Runs the prompt to read heredoc input from the user.
 * 
 * This function displays a prompt to the user and reads input
 * until the delimiter is encountered. If dollar expansion is
 * enabled, it processes the input accordingly.
 * 
 * @param node The current AST node.
 * @param fd The file descriptor to write the input to.
 * @param is_dollar Indicates if dollar expansion is enabled.
 * @param ms The minishell context.
 * @return int The exit code of the prompt.
 */
static int	run_prompt(t_ast *node, int fd, t_bool is_dollar, t_mshell *ms)
{
	char	*input;

	input = NULL;
	while (TRUE)
	{
		input = readline("> ");
		if (g_status == 128 + SIGINT)
		{
			sig_to_exit_code(ms);
			exe_close_fd(&fd);
			break ;
		}
		if (!input)
			return (ms->exit_code);
		if (ft_strcmp(input, node->value[0]) == 0)
			break ;
		if (is_dollar)
			exe_handle_dollar_expansion(input, fd, ms);
		else
			write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	return (ms->exit_code);
}

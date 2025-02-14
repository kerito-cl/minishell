/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:47:55 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/14 15:11:33 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	handle_redir_input(t_ast *node);
static int	handle_redir_heredoc(t_ast *node);
static int	handle_redir_output(t_ast *node);
static int	handle_redir_append(t_ast *node);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Executes the redirection commands.
 * 
 * @param node Pointer to the AST node representing the redirection command.
 * @param ms Pointer to the minishell structure containing the shell state.
 * @return int Returns 0 on success, or an error code on failure.
 */
int	exe_redirection(t_ast *node, t_mshell *ms)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), (errno));
	if (pid == 0)
	{
		sig_interceptor(SIG_DEFAULT_MODE);
		if (node->type == REIN)
			ms->exit_code = handle_redir_input(node);
		if (node->type == REIN2)
			ms->exit_code = handle_redir_heredoc(node);
		else if (node->type == REOUT)
			ms->exit_code = handle_redir_output(node);
		else if (node->type == REOUT2)
			ms->exit_code = handle_redir_append(node);
		if (ms->exit_code != 0)
			exit(ms->exit_code);
		ms->exit_code = exe_ast_tree(node->left, ms);
		ms->exit_code = exe_ast_tree(node->right, ms);
		exit(ms->exit_code);
	}
	ms->exit_code = exe_wait_children(&pid, 1);
	return (ms->exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Handles input redirection.
 * 
 * This function opens the input file 
 * and duplicates the file descriptor to STDIN.
 * 
 * @param node Pointer to the AST node.
 * @return int Returns 0 on success, or an error code on failure.
 */
static int	handle_redir_input(t_ast *node)
{
	int	fd;

	fd = open(node->value[0], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: redir_input: ", STDERR_FILENO);
		perror(node->value[0]);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("minishell: dup2");
		return (errno);
	}
	close(fd);
	return (0);
}

/**
 * @brief Handles the redirection for a heredoc.
 * 
 * This function duplicates the file descriptor stored in the node 
 * to the standard input (STDIN_FILENO).
 * 
 * @param node A pointer to the AST node.
 * @return int Returns 0 on success, or the error number on failure.
 */
static int	handle_redir_heredoc(t_ast *node)
{
	if (dup2(node->fd, STDIN_FILENO) == -1)
	{
		close(node->fd);
		node->fd = -1;
		perror("minishell: dup2");
		return (errno);
	}
	close(node->fd);
	return (0);
}

/**
 * @brief Handles output redirection.
 * 
 * This function opens the output file 
 * and duplicates the file descriptor to STDOUT.
 * 
 * @param node Pointer to the AST node.
 * @return int Returns 0 on success, or an error code on failure.
 */
static int	handle_redir_output(t_ast *node)
{
	int	fd;

	fd = open(node->value[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: redir_output: ", STDERR_FILENO);
		perror(node->value[0]);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("minishell: dup2");
		return (errno);
	}
	close(fd);
	return (0);
}

/**
 * @brief Handles append redirection.
 * 
 * This function opens the output file in append mode 
 * and duplicates the file descriptor to STDOUT.
 * 
 * @param node Pointer to the AST node.
 * @return int Returns 0 on success, or an error code on failure.
 */
static int	handle_redir_append(t_ast *node)
{
	int	fd;

	fd = open(node->value[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: redir_append: ", STDERR_FILENO);
		perror(node->value[0]);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("minishell: dup2");
		return (errno);
	}
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc_preprocessor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:12:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/16 21:37:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	exe_heredoc(t_ast *node, t_mshell *ms);
static void	handle_heredoc_fork(t_ast *node, int fd[2], t_mshell *ms);
static int	run_prompt(t_ast *node, int fd, t_bool is_dollar, t_mshell *ms);
static char	*get_user_input(void);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Preprocesses the heredoc nodes in the AST.
 * 
 * This function recursively processes the AST nodes to handle heredoc
 * redirections. It calls exe_heredoc for nodes of type REIN2 and
 * continues processing the left and right children of the node.
 * 
 * @param node The current AST node.
 * @param ms The minishell context.
 * @return int The exit code of the heredoc processing.
 */
int	exe_heredoc_preprocessor(t_ast *node, t_mshell *ms)
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

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Executes the heredoc for a given AST node.
 * 
 * @param node The current AST node.
 * @param ms The minishell context.
 * @return int The exit code of the heredoc execution.
 */
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
	sig_interceptor(SIG_HEREDOC_MODE);
	exe_close_fd(&fd[FD_READ]);
	run_prompt(node, fd[FD_WRITE], ft_strchr(node->value[0], '$') != NULL, ms);
	exe_close_fd(&fd[FD_WRITE]);
	exit(EXIT_SUCCESS);
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
		input = get_user_input();
		if (!input)
			return (0);
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
	get_next_line(STDIN_FILENO, TRUE);
	return (0);
}

/**
 * @brief Prompts the user for input and reads a line from standard input.
 * 
 * This function displays a prompt ("> ") to the user, reads a line of input
 * from the standard input, and removes the newline character if present.
 * 
 * @return char* A pointer to the input string, or NULL if an error occurs or 
 *         end-of-file is reached.
 */
static char	*get_user_input(void)
{
	char	*input;
	char	*nl;

	input = NULL;
	nl = NULL;
	ft_putstr_fd("> ", STDOUT_FILENO);
	input = get_next_line(STDIN_FILENO, FALSE);
	if (!input)
		return (NULL);
	nl = ft_strchr(input, '\n');
	if (nl != NULL)
		*nl = '\0';
	return (input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc_preprocessor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:12:25 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/17 08:31:13 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

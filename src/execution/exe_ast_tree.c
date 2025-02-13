/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_ast_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:19:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/13 18:17:56 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the abstract syntax tree (AST) node.
 * 
 * This function takes an AST node and the minishell context, and executes
 * the command or operation represented by the node.
 * 
 * @param node A pointer to the AST node to be executed.
 * @param ms A pointer to the minishell context.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
int	exe_ast_tree(t_ast *node, t_mshell *ms)
{
	if (!node || !ms)
		return (0);
	if (node->type == PIPE)
		ms->exit_code = exe_pipe(node, ms);
	else if (node->type == CMD)
		ms->exit_code = exe_command(node, ms);
	else if (node->type >= REIN && node->type <= REOUT2)
		ms->exit_code = exe_redirection(node, ms);
	return (ms->exit_code);
}

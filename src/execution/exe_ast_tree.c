/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_ast_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:19:31 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/23 15:35:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_ast_tree(t_ast *node, t_mshell *ms)
{
	if (!node || !ms)
		return (0);
	if (node->type == PIPE)
		ms->exit_code = exe_pipe(node, ms);
	else if (node->type == CMD)
		printf("I'm command %s\n", node->value); //ms->exit_code = exe_command(node, ms);
	else if (node->type >= REIN && node->type <= REOUT2)
		printf("I'm redirection node (%d).\n", node->type);
	else if (node->type == ARG)
		printf("I'm ARG node (%d).\n", ARG);
	return (0);
}

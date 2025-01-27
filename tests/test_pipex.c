/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:12:30 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/23 15:25:26 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_pipex_exernal_cmd(char *cmd1, char *cmd2, t_mshell *ms)
{
	t_ast root;
	t_ast left;
	t_ast right;
	
	root.left = &left;
	root.right = &right;
	root.type = PIPE;
	root.value = "|";

	left.value = cmd1;
	left.left = NULL;
	left.right = NULL;
	left.type = CMD;

	right.value = cmd2;
	right.left = NULL;
	right.right = NULL;
	right.type = CMD;

	ms->exit_code = exe_pipe(&root, ms);
	printf("exit code: %d\n", ms->exit_code);
}
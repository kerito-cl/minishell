/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc_preprocessor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:19:16 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/13 01:57:03 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_ast *node, t_mshell *ms);
static char	**create_file_name(t_ast *node);

int exe_heredoc_preprocessor(t_ast *node, t_mshell *ms)
{
	ms->exit_code = 0;
    if (node == NULL) {
        return (ms->exit_code);
    }
    if (node->type == REIN2)
		ms->exit_code = handle_heredoc(node, ms);
	if (ms->exit_code != 0)
		return(ms->exit_code);
	ms->exit_code = exe_heredoc_preprocessor(node->left, ms);
	if (ms->exit_code == 0)
		ms->exit_code = exe_heredoc_preprocessor(node->right, ms);
	return (ms->exit_code);
}

static int	handle_heredoc(t_ast *node, t_mshell *ms)
{
	pid_t	pid;
	int		fd;

	node->value = create_file_name(node);
	if (!node->value || !node->value[0])
		return (errno);
	fd = open(node->value[0], O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("minishell: open");
		return (errno);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (errno);
	}
	if (pid == 0)
		run_heredoc_prompt(fd);
	close(fd);
	ms->exit_code = exe_wait_children(&pid, 1);
	return (ms->exit_code);
}

static char	**create_file_name(t_ast *node)
{
	return(NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:41:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 14:33:32 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_command(char **args, t_mshell *ms);
static int	run_external(char **args, t_mshell *ms);

int	exe_command(t_ast *node, t_mshell *ms)
{
	char		**parse_input;

	if (!node || !ms)
		return (0);
	parse_input = ft_split(node->value, ' ');
	if (!parse_input)
		return (ERROR_MALLOC_FAILS);
	if (parse_input[0] == NULL || parse_input[0][0] == '\0')
	{
		free_2d_array(parse_input, 0);
		return (0);
	}
	ms->exit_code = run_command(parse_input, ms);
	free_2d_array(parse_input, 0);
	return (ms->exit_code);
}

static int	run_command(char **args, t_mshell *ms)
{
	char	*cmd;

	cmd = args[0];
	if (ft_strcmp(cmd, "cd") == 0)
		ms->exit_code = builtin_cd(args + 1, &ms->env);
	else if (ft_strcmp(cmd, "echo") == 0)
		ms->exit_code = builtin_echo(args + 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		ms->exit_code = builtin_exit(args + 1, ms);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ms->exit_code = builtin_pwd(args + 1);
	else if (ft_strcmp(cmd, "export") == 0)
		ms->exit_code = builtin_export(args + 1, &ms->env);
	else if (ft_strcmp(cmd, "unset") == 0)
		ms->exit_code = builtin_unset(args + 1, &ms->env);
	else
		ms->exit_code = run_external(args, ms);
	return (ms->exit_code);
}

static int	run_external(char **args, t_mshell *ms)
{
	char	path[PATH_MAX];

	path[0] = '\0';
	if (!exe_search_cmd_path(*args, env_find_value("PATH", &ms->env), path))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (ERROR_CMD_NOT_FOUND);
	}
	if (execve(path, args, ms->env.envp) == -1)
	{
		perror("minishell: execve");
		return (errno);
	}
	return (0);
}

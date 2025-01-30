/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:41:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/27 11:14:09 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	run_command(char **args, t_mshell *ms);
static int	run_external(char **args, t_mshell *ms);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Executes a command node in the abstract syntax tree (AST) 
 * 
 * @param node A pointer to the command node in the AST to be executed.
 * @param ms A pointer to the minishell instance.
 * @return int The result of the command execution.
 */
int	exe_command(t_ast *node, t_mshell *ms)
{
	char		**input;

	if (!node || !ms)
		return (0);
	input = node->value;
	if (input[0] == NULL || input[0][0] == '\0')
		return (0);
	ms->exit_code = exe_check_special_case(input + 1, ms);
	if (ms->exit_code == 0)
		ms->exit_code = run_command(input, ms);
	return (ms->exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Executes a command with given arguments.
 * 
 * @param args An array of strings representing the command and its arguments.
 * @param ms A pointer to the minishell structure.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
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

/**
 * @brief Executes an external command.
 * 
 * This function is responsible for running an external command by forking 
 * a new process and executing the command specified in the arguments.
 * 
 * @param args A null-terminated array of the command and its arguments.
 * @param ms A pointer to the minishell structure.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
static int	run_external(char **args, t_mshell *ms)
{
	char	path[PATH_MAX];
	pid_t	pid;

	path[0] = '\0';
	if (!exe_search_cmd_path(*args, env_find_value("PATH", &ms->env), path))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (ERROR_CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == 0 && execve(path, args, ms->env.envp) == -1)
	{
		perror("minishell: execve");
		return (errno);
	}
	ms->exit_code = exe_wait_children(&pid, 1);
	return (ms->exit_code);
}

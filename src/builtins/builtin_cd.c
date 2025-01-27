/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:55:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 15:48:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	go_home(t_env *env);
static int	go_path(const char *path, t_env *env);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Changes the current working directory based on the arguments.
 * 
 * if no args -> go home, 
 * if no HOME var -> error `cd: HOME not set` (exit code = 1)
 * if more than 2 args -> error `cd: too many arguments` (exit code = 1)
 * if first argument start with `-` -> `cd: options aren't supported`
 * if path doesn't exist -> error `cd: Do: No such file or directory`
 * 
 * @param args Arguments passed to the `cd` command.
 * @param env Pointer to the environment structure.
 * @return `0` on success, error code on failure.
 */
int	builtin_cd(char **args, t_env *env)
{
	if (!args || args[0] == NULL)
		return (go_home(env));
	if (args[1] != NULL && args[0][0] != '-')
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (ERROR_GENERIC);
	}
	if (args[0][0] == '-')
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		ft_putstr_fd("cd: usage: cd [dir]\n", STDERR_FILENO);
		return (ERROR_INVALID_OPTION);
	}
	return (go_path(args[0], env));
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Changes the directory to the home directory.
 * 
 * Retrieves the `HOME` environment variable and changes to it. 
 * Returns an error if `HOME` is not set.
 * 
 * @param env Pointer to the environment structure.
 * @return `0` on success, `ERROR_GENERIC` if `HOME` is not set.
 */
static int	go_home(t_env *env)
{
	const char	*home_path;

	home_path = env_find_value("HOME", env);
	if (!home_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (ERROR_GENERIC);
	}
	return (go_path(home_path, env));
}

/**
 * @brief Changes the current directory to the specified path.
 * 
 * Changes to the provided path and updates the `PWD` 
 * and `OLDPWD` environment variables. Returns error codes 
 * if the directory change fails.
 * 
 * @param path The target directory.
 * @param env Pointer to the environment structure.
 * @return `0` on success, error code on failure.
 */
static int	go_path(const char *path, t_env *env)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	if (!old_path || chdir(path) == -1)
	{
		free(old_path);
		perror("minishell: cd");
		return (ERROR_GENERIC);
	}
	builtin_update_env_var("OLDPWD", old_path, env);
	free(old_path);
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("minishell: cd");
		return (ERROR_GENERIC);
	}
	builtin_update_env_var("PWD", new_path, env);
	free(new_path);
	return (0);
}

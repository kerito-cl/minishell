/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:55:21 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/17 11:57:24 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	go_home(t_env *env);
static int	go_path(const char *path, t_env *env);
static void	update_env_path(t_env *env, char *curr_path, const char *path);

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
		return ((go_home(env)));
	if (args[0][0] == '-')
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		ft_putstr_fd("cd: usage: cd [dir]\n", STDERR_FILENO);
		return (ERROR_INVALID_OPTION);
	}
	if (args[1] != NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (ERROR_GENERIC);
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
 * @brief Changes the cwd to the specified path and updates the env variables.
 * 
 * @param path The path to the directory to change to.
 * @param env The environment structure to update.
 * @return int Returns 0 on success, or an error code on failure.
 */
static int	go_path(const char *path, t_env *env)
{
	char	*curr_path;

	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
		return (ERROR_GENERIC);
	}
	curr_path = getcwd(NULL, 0);
	if (!curr_path)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		perror("getcwd: cannot access parent directories");
	}
	update_env_path(env, curr_path, path);
	if (curr_path)
		free(curr_path);
	return (0);
}

/**
 * @brief Updates the env variables related to the current 
 * 		  and old working directories.
 * 
 * This function updates the "PWD" and "OLDPWD" environment variables.
 * 
 * @param env Pointer to the environment structure.
 * @param curr_path The current path to be set as the new "PWD" value.
 * @param path The path to be appended to the previous "PWD" value 
 * 			   if curr_path is NULL.
 */
static void	update_env_path(t_env *env, char *curr_path, const char *path)
{
	const char	*tmp;
	char		*new_pwd;

	tmp = env_find_value("PWD", env);
	if (tmp == NULL)
		builtin_update_env_var("OLDPWD", "", env);
	else
		builtin_update_env_var("OLDPWD", tmp, env);
	if (curr_path != NULL)
		return (builtin_update_env_var("PWD", curr_path, env));
	if (curr_path == NULL && tmp == NULL)
		return ;
	new_pwd = ft_strjoin(tmp, "/");
	if (!new_pwd)
		return (perror("minishell: malloc"));
	curr_path = ft_strjoin(new_pwd, path);
	free(new_pwd);
	if (!curr_path)
		return (perror("minishell: malloc"));
	builtin_update_env_var("PWD", curr_path, env);
	free(curr_path);
	curr_path = NULL;
}

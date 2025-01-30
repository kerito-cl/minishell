/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_search_cmd_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:54:49 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/30 19:24:49 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static char	*get_full_path(const char *cmd, const char *root, char *dst);
static int	check_own_path(const char *cmd, char *path);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Searches for the command path in the given environment path.
 * 
 * This function attempts to locate the full path of a command by searching
 * through the directories listed in the environment PATH variable.
 * 
 * @param cmd The command to search for.
 * @param env_path The environment path variable with directories to search.
 * @param path A buffer to store the found command path.
 * @return char* The full path to the command if found, otherwise NULL.
 */
char	*exe_search_cmd_path(const char *cmd, const char *env_path, char *path)
{
	char	**arr;
	int		i;

	if (!cmd || !env_path || env_path[0] == '\0' || !path)
		return (NULL);
	if (check_own_path(cmd, path) == 0)
		return (path);
	arr = ft_split(env_path, ':');
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		if (get_full_path(cmd, arr[i++], path) != NULL)
		{
			if (access(path, X_OK) == 0)
			{
				free_2d_array(arr, 0);
				return (path);
			}
		}
	}
	path[0] = '\0';
	free_2d_array(arr, 0);
	return (NULL);
}

static int	check_own_path(const char *cmd, char *path)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (access(cmd, X_OK) == 0 && len < PATH_MAX)
	{
		ft_memcpy(path, cmd, len);
		path[len] = '\0';
		return (0);
	}
	return (1);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Constructs the full path to the command.
 * 
 * @param cmd The name of the command.
 * @param root The root path where the command could be located.
 * @param dst The buffer where the constructed full path will be stored.
 * @return char* Pointer to the destination buffer containing the full path.
 */
static char	*get_full_path(const char *cmd, const char *root, char *dst)
{
	size_t	len_root;
	size_t	len_cmd;

	len_root = ft_strlen(root);
	len_cmd = ft_strlen(cmd);
	if ((len_cmd + len_root + 1) >= PATH_MAX)
		return (NULL);
	ft_memcpy(dst, root, len_root);
	dst[len_root++] = '/';
	ft_memcpy(dst + len_root, cmd, len_cmd);
	dst[len_root + len_cmd] = '\0';
	return (dst);
}

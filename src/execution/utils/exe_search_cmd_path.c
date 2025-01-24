/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_search_cmd_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:54:49 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 12:19:50 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_path(const char *cmd, const char *root, char *dst);

char	*exe_search_cmd_path(const char *cmd, const char *env_path, char *path)
{
	char	**arr;
	int		i;

	if (!cmd || !env_path || env_path[0] == '\0' || !path)
		return (NULL);
	arr = ft_split(env_path, ':');
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		if (get_full_path(cmd, arr[i], path) != NULL)
		{
			if (access(path, X_OK) == 0)
			{
				free_2d_array(arr, 0);
				return (path);
			}
		}
		i++;
	}
	path[0] = '\0';
	free_2d_array(arr, 0);
	return (NULL);
}


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

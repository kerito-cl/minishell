/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_search_cmd_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:54:49 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 01:23:53 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exe_search_cmd_path(char *cmd, char *env_path, char *path[PATH_MAX])
{
	char	**arr;
	int		i;
	int		j;
	int		len;

	if (!cmd || !env_path || env_path[0] == '\0' || !path)
		return (NULL);
	arr = ft_split(env_path, ':');
	if (arr)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		len = ft_min(PATH_MAX - 1, ft_strlen(arr[i]));
		ft_memcpy(*path, arr[i], len);
		*path[len++] = '/';
		j = 0;
		while (len < PATH_MAX - 1 && cmd[j] != '\0')
			*path[len++] = cmd[j++];
		*path[len] = '\0';
		if (access(path, X_OK) == 0)
		{
			free_2d_array(arr, 0);
			return (*path);
		}
		i++;
	}
	free_2d_array(arr, 0);
	return (NULL);
}

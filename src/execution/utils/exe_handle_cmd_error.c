/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_handle_cmd_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 03:27:45 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/15 04:40:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static t_bool	is_regular_file(struct stat *st);

/* --------------------------- Public Functions ---------------------------- */

int	exe_handle_cmd_error(char *path)
{
	struct stat	st;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (stat(path, &st) == -1)
	{
		if (ft_strchr(path, '/') != NULL)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (ERROR_CMD_NOT_FOUND);
	}
	if (!is_regular_file(&st))
		return (ERROR_ISDIR);
	if (path[0] == '.' && path[1] == '/')
	{
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (ERROR_ISDIR);
	}
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (ERROR_CMD_NOT_FOUND);
}

/* ------------------- Private Function Implementation --------------------- */

static t_bool	is_regular_file(struct stat *st)
{
	if (!S_ISREG(st->st_mode))
	{
		if (S_ISDIR(st->st_mode))
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Not a regular file\n", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:13:12 by mquero            #+#    #+#             */
/*   Updated: 2024/12/28 14:42:56 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(t_fd *fd)
{
	close(fd->pipe[0]);
	close(fd->pipe[1]);
	if (fd->output != -1)
		close(fd->output);
	if (fd->input != -1)
		close(fd->input);
}

void	throw_error_child(char *path, t_fd *fd, char *arg)
{
	if (path == NULL)
		ft_printf("pipex: command not found: %s\n", arg);
	if (path != NULL)
	{
		free(path);
	}
	close_all(fd);
	if (fd->input == -1 || fd->output == -1)
		exit(1);
	else
		exit(127);
}

void	error_ifdir(char *str)
{
	ft_printf("pipex: ");
	perror(str);
}

void	e_free_e(char *str, char **split)
{
	perror(str);
	free(str);
	freesplit(split);
	exit(126);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:50:40 by mquero            #+#    #+#             */
/*   Updated: 2025/01/13 23:20:15 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "./printf/ft_printf.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef struct s_fd
{
	int		pipe[2];
	char	*path1;
	char	*path2;
	char	**split;
	int		input;
	int		output;
	int		status;
	int		pid1;
	int		pid2;
}			t_fd;

typedef struct s_in
{
	char	**cmds;
	char	*input;
	char	*path;
	int		n_pipes;
	int		n_infiles;
	int		n_outfiles;
	int		status;
	int		pid1;
	int		pid2;
}			t_in;

char		*ft_strjoin(char const *s1, char const *s2);
void		freesplit(char **strs);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *s);
void		child1(t_fd fd, char **argv, char **envp);
void		child2(t_fd fd, char **argv, char **envp);
void		close_all(t_fd *fd);
void		throw_error_child(char *path, t_fd *fd, char *arg);
void		error_ifdir(char *str);
void		e_free_e(char *str, char **split);
char		*find_path(char *argv, char **envp, int i);
void		parse(char *input);
void		slash_signal(int sig);
int			hook_signal(void);
void		continue_signal(int sig);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:50:40 by mquero            #+#    #+#             */
/*   Updated: 2025/01/20 16:25:34 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum {
    PIPE = 22,
    REIN,
    REIN2,
    REOUT,
    REOUT2,
    SQUOTE,
    DQUOTE,
    ARG,
} tokentype;

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
typedef struct s_index
{
	int		pip;
	int		pip_h;
	int		i;
	int		min;
	int		max;
	int		prior;
	int		i_reout;
	bool	reout;
	bool	rein;

}			t_index;

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

typedef struct s_token
{
	char *value;
	tokentype type;
	int	j;
}			t_token;

typedef struct s_ast
{
	char	*value;
	tokentype type;          
	struct s_ast *left;  
	struct s_ast *right;
}			t_ast;

char		*ft_strjoin_slash(char const *s1, char const *s2);
void		freesplit(char **strs);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
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
char		*ft_strjoin(char *s1, char const *s2);
char		**assign_value(char **split, int left, int right);
int			ft_strcmp(const char *s1, char *s2);
char		*ft_strdup(const char *s, size_t n);
size_t	ft_strlen(const char *str);

#endif
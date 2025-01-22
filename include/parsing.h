/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:08 by mquero            #+#    #+#             */
/*   Updated: 2025/01/21 21:15:11 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef PARSING_H
# define PARSING_H

typedef enum
{
	PIPE = 22,
	REIN,
	REIN2,
	REOUT,
	REOUT2,
	ARG,
	CMD,
}					tokentype;

typedef struct s_token
{
	char			*value;
	tokentype		type;
	bool			lock;
}					t_token;

typedef struct s_ast
{
	char			*value;
	tokentype		type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_index
{
	int				pip;
	int				key;
	int				min;
	int				max;
	int				len;

}					t_index;

int					ft_strcmp(const char *s1, char *s2);
void				ft_bzero(void *s, size_t n);
char				*ft_strndup(const char *s, size_t n);
size_t				ft_strlen(const char *str);
t_ast				*create_node(char *s1, tokentype type);
int					tokenize(t_token *tokens, char *input);
t_ast				*parse_input(char *input);
void				assign_to_right(t_ast *root, t_token *tokens, t_index *i);
void				assign_to_left(t_ast *root, t_token *tokens, t_index *i,
						bool flag);
void				find_root(t_ast **root, t_token *tokens, t_index *i);
void				free_tokens(t_token *tokens, int len);
void				free_ast(t_ast *node);

#endif
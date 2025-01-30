/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:34:08 by mquero            #+#    #+#             */
/*   Updated: 2025/01/29 13:11:44 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_tokentype
{
	PIPE = 22,
	REIN,
	REIN2,
	REOUT,
	REOUT2,
	ARG,
	CMD,
}					t_tokentype;

typedef struct s_token
{
	char			*value;
	char			**cmd;
	t_tokentype		type;
	bool			lock;
	bool			has_dollar;
	char			quote;
}					t_token;

typedef struct s_ast
{
	char			**value;
	t_tokentype		type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct s_flags
{
	bool			a;
	bool			b;
	bool			c;
}					t_flags;

typedef struct s_elem
{
	int				i;
	int				k;
	int				y;
	int				j;
	size_t			len;
	size_t			new_len;
	char			quote;
}					t_elem;

typedef struct s_index
{
	int				pip;
	int				key;
	int				min;
	int				max;
	int				len;

}					t_index;

void				ft_bzero(void *s, size_t n);
char				*ft_strndup(char *s, size_t n);
t_ast				*create_node(char **s1, t_tokentype type);
int					tokenize(t_token *tokens, char *input);
t_ast				*parse_input(char *input, char **envp);
void				assign_to_right(t_ast *root, t_token *tokens, t_index *i);
void				assign_to_left(t_ast *root, t_token *tokens, t_index *i,
						bool flag);
void				find_root(t_ast **root, t_token *tokens, t_index *i);
void				free_tokens(t_token *tokens, int len);
void				free_ast(t_ast *node);
char				*deal_with_quotes(char *input);
char				**create_cmd(char *s);
bool				compare_token(char *buffer, int i, bool flag, char quote);
char				quote_value(char c);
char				**cpy_cmds(char **strs);
char    			*handle_dollar_sign(char *input, char **envp);
char				*env_find_variable_v2(const char *var, t_env *env, size_t *i);
char				*env_find_value_v2(const char *var, t_env *env);
bool				check_parse_error(t_token *tokens, int len);

#endif
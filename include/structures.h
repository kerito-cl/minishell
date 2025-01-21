/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:35:41 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/21 18:38:38 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/* ------------------------------ Environment ------------------------------ */

typedef struct s_env
{
	char			**envp;
	unsigned int	len;
	unsigned int	capacity;	
}	t_env;

/* ------------------------------- Minishell ------------------------------- */

typedef struct s_mshell
{
	t_env	env;
	int		exit_code;
	int		is_parent;
}			t_mshell;

/* -------------------------- Abstract syntax tree -------------------------- */

typedef enum e_tokentype {
    PIPE = 22,
    REIN,
    REIN2,
    REOUT,
    REOUT2,
    SQUOTE,
    DQUOTE,
    ARG
}	t_tokentype;

typedef struct s_ast
{
	char			*value;
	t_tokentype		type;          
	struct s_ast	*left;  
	struct s_ast	*right;
}					t_ast;

#endif
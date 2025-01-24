/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:35:41 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 22:31:38 by ipersids         ###   ########.fr       */
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
	int		interactive_mode;
}			t_mshell;

#endif
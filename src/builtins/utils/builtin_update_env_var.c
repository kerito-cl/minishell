/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_update_env_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:22 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/23 11:27:35 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_update_env_var(const char *name, const char *value, t_env *env)
{
	char	*tmp;
	size_t	i;
	size_t	len;
	size_t	capacity;

	i = 0;
	if (!name || !value || !env || !env_find_variable(name, env, &i))
		return ;
	capacity = ft_strlen(name) + ft_strlen(value) + 2;
	tmp = (char *) malloc(capacity * sizeof(char));
	if (!tmp)
		return (perror("minishell: cd: "));
	len = 0;
	i = 0;
	while (name[i] != '=' && name[i] != '\0')
		tmp[len++] = name[i++];
	tmp[len++] = '=';
	i = 0;
	while (value[i] != '\0')
		tmp[len++] = value[i++];
	tmp[len] = '\0';
	env_add(tmp, env);
	free(tmp);
}

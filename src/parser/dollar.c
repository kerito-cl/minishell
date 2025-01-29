/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:10:10 by mquero            #+#    #+#             */
/*   Updated: 2025/01/29 10:21:22 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env_var(char **var, t_elem *elem, char **input, char **envp)
{
	t_env	envir;
	char	*temp;

	envir.envp = envp;
	temp = env_find_value_v2(*input, &envir);
	if (temp != NULL)
	{
		elem->new_len = elem->len + ft_strlen(temp);
		*var = ft_realloc(*var, elem->len, elem->new_len);
		if (!*var)
			exit(1);
		elem->len = elem->new_len;
		while (*temp)
		{
			(*var)[elem->i] = *temp;
			elem->i++;
			temp++;
		}
	}
	while (**input != '\0' && !ft_strchr(" \"'<>|", **input))
		*input += 1;
}

static void	cpy_if_no_dollar(char **input, char *var, t_elem *elem)
{
	while (**input != '$' && **input)
	{
		if (**input == '\'')
		{
			var[elem->i] = **input;
			elem->i++;
			*input += 1;
			while (**input && **input != '\'')
			{
				var[elem->i] = **input;
				elem->i++;
				*input += 1;
			}
		}
		else
		{
			var[elem->i] = **input;
			elem->i++;
			*input += 1;
		}
	}
}

char	*handle_dollar_sign(char *input, char **envp)
{
	char	*var;
	t_elem	elem;

	elem.i = 0;
	elem.len = ft_strlen(input);
	elem.new_len = ft_strlen(input);
	var = ft_calloc(sizeof(char), (elem.len + 1));
	if (!var)
		exit(1);
	while (*input)
	{
		cpy_if_no_dollar(&input, var, &elem);
		if (*input == '$' && (!input[1] || ft_strchr(" \"'<>|", input[1])))
		{
			var[elem.i] = *input;
			elem.i++;
			input++;
		}
		else if (*input == '$' && input[1] != '\0')
			expand_env_var(&var, &elem, &input, envp);
		else if (*input != '\0')
			input++;
	}
	var[elem.i] = '\0';
	return (var);
}

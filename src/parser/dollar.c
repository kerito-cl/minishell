/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:10:10 by mquero            #+#    #+#             */
/*   Updated: 2025/02/13 21:24:57 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_if_heredoc(char **input, char *var, t_elem *elem)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		var[elem->i++] = **input;
		*input += 1;
		var[elem->i++] = **input;
		*input += 1;
		while (**input == ' ' || **input == '\t')
			*input += 1;
		while (**input != '\0' && !ft_strchr(" \t<>|", **input))
		{
			var[elem->i++] = **input;
			*input += 1;
		}
	}
}

static void	expand_env_var(char **var, t_elem *elem, char **input, char **envp)
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
	*input += 1;
	while (**input != '\0' && !ft_strchr(" \t\"'<>|$", **input))
		*input += 1;
}

static void	cpy_if_no_dollar(char **input, char *var, t_elem *elem)
{
	while (**input != '$' && **input)
	{
		check_if_heredoc(input, var, elem);
		if (**input == '\'')
		{
			var[elem->i++] = **input;
			*input += 1;
			while (**input && **input != '\'')
			{
				var[elem->i++] = **input;
				*input += 1;
			}
			if (**input == '\'')
			{
				var[elem->i++] = **input;
				*input += 1;
			}
		}
		else
		{
			var[elem->i++] = **input;
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
	var = ft_calloc(sizeof(char), (elem.len + 2));
	if (!var)
		exit(1);
	while (*input)
	{
		cpy_if_no_dollar(&input, var, &elem);
		if (*input == '$' && (!input[1] || ft_strchr(" \t\"'<>|$?", input[1])))
			var[elem.i++] = *input++;
		else if (*input == '$' && input[1] != '\0')
			expand_env_var(&var, &elem, &input, envp);
		else if (*input != '\0')
			input++;
	}
	var[elem.i] = '\0';
	if (var[0] == 0)
		return (free(var), NULL);
	return (var);
}

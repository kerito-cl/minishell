/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:37:38 by mquero            #+#    #+#             */
/*   Updated: 2025/01/27 11:17:49 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	compare_token(char *buffer, int i, bool flag, char quote)
{
	if (quote == 0)
	{
		if (buffer[i] == '<' || buffer[i] == '>')
			return (false);
		if (buffer[i] == '|')
			return (false);
		if (buffer[i] == ' ' && flag == true)
			return (false);
	}
	return (true);
}

char	quote_value(char c)
{
	char	quote;

	if (c == '\'')
		quote = '\'';
	else if (c == '\"')
		quote = '\"';
	else
		quote = '\0';
	return (quote);
}

char	**cpy_cmds(char **strs)
{
	char	**cmd;
	int		i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		exit(1);
	cmd[i] = NULL;
	i = 0;
	while (strs[i])
	{
		cmd[i] = ft_strndup(strs[i], ft_strlen(strs[i]));
		if (!cmd[i])
			exit(1);
		i++;
	}
	return (cmd);
}

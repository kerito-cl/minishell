/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:37:38 by mquero            #+#    #+#             */
/*   Updated: 2025/01/30 10:13:48 by mquero           ###   ########.fr       */
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

static void	write_parse_error(t_tokentype type)
{
	if (type == PIPE)
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
	if (type == REIN)
		write (2, "minishell: syntax error near unexpected token `<'\n", 51);
	if (type == REIN2)
		write (2, "minishell: syntax error near unexpected token `<<'\n", 52);
	if (type == REOUT)
		write (2, "minishell: syntax error near unexpected token `>'\n", 51);
	if (type == REOUT2)
		write (2, "minishell: syntax error near unexpected token `>>'\n", 52);
}

bool	check_parse_error(t_token *tokens, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tokens[i].type != ARG && tokens[i + 1].type != ARG)
		{
			write_parse_error(tokens[i].type);
			free_tokens(tokens, len);
			return (false);
		}
		i++;
	}
	return (true);
}

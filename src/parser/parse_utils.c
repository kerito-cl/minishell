/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:37:38 by mquero            #+#    #+#             */
/*   Updated: 2025/01/31 13:14:58 by mquero           ###   ########.fr       */
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

static void	write_parse_error(t_token *tokens, t_tokentype type, int len)
{
	if (type == PIPE)
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
	if (type == REIN)
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
	if (type == REIN2)
		write(2, "minishell: syntax error near unexpected token `<<'\n", 52);
	if (type == REOUT)
		write(2, "minishell: syntax error near unexpected token `>'\n", 51);
	if (type == REOUT2)
		write(2, "minishell: syntax error near unexpected token `>>'\n", 52);
	free_tokens(tokens, len);
}

bool	check_parse_error(t_token *tokens, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tokens[0].type == PIPE)
		{
			write_parse_error(tokens, tokens[0].type, len);
			return (false);
		}
		if (i != 0 && tokens[i].type == PIPE && tokens[i - 1].type != ARG)
		{
			write_parse_error(tokens, tokens[i].type, len);
			return (false);
		}
		if (tokens[i].type != PIPE && tokens[i].type != ARG && tokens[i
			+ 1].type != ARG)
		{
			write_parse_error(tokens, tokens[i].type, len);
			return (false);
		}
		i++;
	}
	return (true);
}

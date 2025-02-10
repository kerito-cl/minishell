/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:15:29 by mquero            #+#    #+#             */
/*   Updated: 2025/02/06 23:26:52 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	add_type(t_token *tokens, char *buffer, int *i, int *j)
{
	if (buffer[*i] == '<' && buffer[*i + 1] != '<')
	{
		tokens[(*j)++].type = REIN;
		return (true);
	}
	else if (buffer[*i] == '<' && buffer[*i + 1] == '<')
	{
		tokens[(*j)++].type = REIN2;
		*i += 1;
		return (true);
	}
	else if (buffer[*i] == '>' && buffer[*i + 1] != '>')
	{
		tokens[(*j)++].type = REOUT;
		return (true);
	}
	else if (buffer[*i] == '>' && buffer[*i + 1] == '>')
	{
		tokens[(*j)++].type = REOUT2;
		*i += 1;
		return (true);
	}
	return (false);
}

bool	add_redirval(t_token *tokens, char *buffer, int *i, int j)
{
	int	k;

	k = *i;
	while (buffer[*i] != '\0')
	{
		if (!compare_token(buffer, *i, true, tokens[j].quote))
		{
			tokens[j].value = ft_strndup(buffer + k, (size_t)(*i - k));
			tokens[j].cmd = create_cmd(tokens[j].value);
			if (!tokens[j].cmd)
				exit_free(tokens, j, buffer);
			tokens[j].type = ARG;
			*i -= 1;
			return (true);
		}
		*i += 1;
	}
	tokens[j].value = ft_strndup(buffer + k, (size_t)(*i - k));
	tokens[j].cmd = create_cmd(tokens[j].value);
	if (!tokens[j].cmd)
		exit_free(tokens, j, buffer);
	tokens[j].type = ARG;
	return (false);
}

bool	add_cmd(t_token *tokens, char *buffer, int *i, int j)
{
	int	k;

	k = *i;
	while (buffer[*i] != '\0')
	{
		if (!compare_token(buffer, *i, false, tokens[j].quote))
		{
			tokens[j].value = ft_strdup_no_op(buffer + k, (size_t)(*i - k));
			tokens[j].cmd = create_cmd(tokens[j].value);
			if (!tokens[j].cmd)
				exit_free(tokens, j, buffer);
			tokens[j].type = ARG;
			*i -= 1;
			return (true);
		}
		if (buffer[*i] == tokens[j].quote && *i != k)
			tokens[j].quote = 0;
		*i += 1;
	}
	tokens[j].value = ft_strdup_no_op(buffer + k, (size_t)(*i - k));
	tokens[j].cmd = create_cmd(tokens[j].value);
	if (!tokens[j].cmd)
		exit_free(tokens, j, buffer);
	tokens[j].type = ARG;
	return (false);
}

static bool	add_all(t_token *tokens, char *buffer, t_elem *elem, bool *flag)
{
	if (add_type(tokens, buffer, &elem->i, &elem->j))
		*flag = true;
	else if (buffer[elem->i] == '|')
	{
		elem->k = 0;
		tokens[elem->j++].type = PIPE;
	}
	else if (*flag == true)
	{
		if (buffer[elem->i] == '\'' || buffer[elem->i] == '\"')
			tokens[elem->j].quote = buffer[elem->i];
		if (!add_redirval(tokens, buffer, &elem->i, elem->j++))
			return (false);
		*flag = false;
	}
	else if (*flag == false && elem->k == 0)
	{
		elem->k = 1;
		if (buffer[elem->i] == '\'' || buffer[elem->i] == '\"')
			tokens[elem->j].quote = buffer[elem->i];
		if (!add_cmd(tokens, buffer, &elem->i, elem->j++))
			return (false);
	}
	return (true);
}

int	tokenize(t_token *tokens, char *input)
{
	t_elem	elem;
	bool	flag;
	char	*buffer;

	elem.i = 0;
	elem.j = 0;
	elem.k = 0;
	flag = false;
	buffer = deal_with_quotes(input);
	if (!buffer)
		return (-1);
	free(input);
	while (buffer[elem.i] != '\0')
	{
		tokens[elem.j].quote = 0;
		while (buffer[elem.i] == ' ')
			elem.i++;
		if (!add_all(tokens, buffer, &elem, &flag))
			break ;
		elem.i++;
	}
	free(buffer);
	return (elem.j);
}

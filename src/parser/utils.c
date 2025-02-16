/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:40:48 by mquero            #+#    #+#             */
/*   Updated: 2025/02/16 11:50:17 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_if_quotes(char *str, char *dest, size_t *i, size_t *j)
{
	char	quote;

	quote = str[*i];
	dest[(*j)++] = str[(*i)++];
	while (str[*i] != quote)
		dest[(*j)++] = str[(*i)++];
	dest[(*j)++] = str[(*i)++];
}

static void	check_if_op(char *str, size_t *i)
{
	char	quote;

	quote = 0;
	(*i)++;
	while (str[*i] == ' ' || str[*i] == '<' || str[*i] == '>')
		(*i)++;
	while (str[*i] != ' ' && str[*i] != '|' && str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			quote = str[(*i)++];
			while (str[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
}

char	*ft_strdup_no_op(char *str, size_t n)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dest = ft_calloc((ft_strlen(str) + 2), sizeof(char));
	if (!dest)
		return (NULL);
	while (i < n)
		dest[j++] = str[i++];
	while (str[i] && str[i] != '|')
	{
		if (str[i] == '\'' || str[i] == '\"')
			check_if_quotes(str, dest, &i, &j);
		if (str[i] == '>' || str[i] == '<')
			check_if_op(str, &i);
		else
		{
			if (str[i] == '|')
				break ;
			dest[j++] = str[i++];
		}
	}
	return (dest);
}

char	*ft_strndup(char *s, size_t n)
{
	char	*des;
	size_t	len;

	des = (char *)ft_calloc(sizeof(char), (n + 2));
	if (des == NULL)
		return (NULL);
	len = 0;
	while (len < n)
	{
		des[len] = s[len];
		len++;
	}
	des[len] = '\0';
	return (des);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

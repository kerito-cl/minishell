/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:19 by mquero            #+#    #+#             */
/*   Updated: 2025/01/27 11:17:40 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increase_counter(int *counter, char *s, int *i, char *quote)
{
	if (s[*i] == '\0')
		*counter += 1;
	while (s[*i])
	{
		if (s[*i] == *quote)
		{
			*counter += 1;
			*i += 1;
			break ;
		}
		else if (*quote == '\0' && s[*i] == ' ')
		{
			*counter += 1;
			*i += 1;
			break ;
		}
		*i += 1;
		if (s[*i] == '\0')
			*counter += 1;
	}
}

int	count_str(char *s)
{
	int		i;
	int		counter;
	char	quote;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		quote = quote_value(s[i]);
		i++;
		increase_counter(&counter, s, &i, &quote);
	}
	return (counter);
}

bool	dupvalues(char *s, char **cmd, t_elem *elem, char quote)
{
	if (s[elem->i] == quote && quote != 0)
	{
		cmd[elem->j] = ft_strndup(s + elem->k, elem->i - elem->k + elem->y);
		elem->j++;
		elem->i++;
		return (false);
	}
	else if (quote == '\0' && s[elem->i] == ' ')
	{
		cmd[elem->j] = ft_strndup(s + elem->k, elem->i - elem->k);
		elem->j++;
		elem->i++;
		return (false);
	}
	elem->i++;
	if (s[elem->i] == '\0' && quote == 0)
	{
		cmd[elem->j] = ft_strndup(s + elem->k, elem->i - elem->k);
		elem->j++;
	}
	return (true);
}

void	loop_val(char *s, char **cmd, t_elem elem)
{
	char	quote;

	while (s[elem.i])
	{
		while (s[elem.i] == ' ')
			elem.i++;
		quote = quote_value(s[elem.i]);
		if (quote != 0)
			elem.i++;
		elem.k = elem.i;
		while (s[elem.i])
		{
			if (s[elem.i] == '$' && quote != 0)
			{
				elem.y = 1;
				elem.k--;
			}
			if (!dupvalues(s, cmd, &elem, quote))
				break ;
		}
	}
}

char	**create_cmd(char *s)
{
	char	**cmd;
	int		counter;
	t_elem	elem;

	elem.y = 0;
	elem.i = 0;
	elem.j = 0;
	counter = count_str(s);
	cmd = (char **)malloc(sizeof(char *) * (counter + 2));
	if (!cmd)
		exit(1);
	cmd[counter] = NULL;
	loop_val(s, cmd, elem);
	free(s);
	return (cmd);
}

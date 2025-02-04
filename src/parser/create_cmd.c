/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:19 by mquero            #+#    #+#             */
/*   Updated: 2025/02/04 11:42:30 by mquero           ###   ########.fr       */
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

static bool	dupvalues(char *s, char **cmd, t_elem *elem, char quote)
{
	if (s[elem->i] == quote && quote != 0)
	{
		cmd[elem->j] = ft_strndup(s + elem->k, elem->i - elem->k + elem->y);
		return (false);
	}
	else if (quote == '\0' && s[elem->i] == ' ')
	{
		cmd[elem->j] = ft_strndup(s + elem->k, elem->i - elem->k);
		return (false);
	}
	elem->i++;
	if (s[elem->i] == '\0' && quote == 0)
	{
		cmd[elem->j] = ft_strndup(s + elem->k, elem->i - elem->k);
		if (!cmd[elem->j])
			return (false);
		elem->j++;
	}
	return (true);
}

bool	loop_val(char *s, char **cmd, t_elem elem)
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
			if (!dupvalues(s, cmd, &elem, quote))
			{
				if (!cmd[elem.j])
					return (false);
				elem.j++;
				elem.i++;
				break ;
			}
		}
	}
	return (true);
}

char	**create_cmd(char *s)
{
	char	**cmd;
	int		counter;
	t_elem	elem;

	if (!s)
		return (NULL);
	elem.y = 0;
	elem.i = 0;
	elem.j = 0;
	counter = count_str(s);
	cmd = (char **)ft_calloc(sizeof(char *), (counter + 2));
	if (!cmd)
	{
		free(s);
		return (NULL);
	}
	cmd[counter] = NULL;
	if (!loop_val(s, cmd, elem))
	{
		free_2d_array(cmd, 0);
		return (NULL);
	}
	free(s);
	return (cmd);
}

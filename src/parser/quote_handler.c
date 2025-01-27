/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:49:00 by mquero            #+#    #+#             */
/*   Updated: 2025/01/27 11:17:57 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_loop(char *input, t_elem *el, t_flags *flag)
{
	while (input[el->k])
	{
		if (input[el->k] == '\'')
		{
			flag->a = true;
			el->quote = '\'';
			break ;
		}
		if (input[el->k] == '\"')
		{
			flag->a = true;
			el->quote = '\"';
			break ;
		}
		if (input[el->k] == ' ')
			break ;
		el->k++;
	}
}

static void	second_loop(char *input, char *buffer, t_elem *el, t_flags *flag)
{
	while (input[el->i])
	{
		if (input[el->i] == ' ')
		{
			flag->b = true;
			break ;
		}
		if (input[el->i] != el->quote)
		{
			buffer[el->j] = input[el->i];
			el->j++;
		}
		if (input[el->i] == el->quote)
		{
			flag->a = true;
			el->i++;
			break ;
		}
		el->i++;
	}
}

static bool	check_quote(char *input, char *buffer, t_elem *el, t_flags *flag)
{
	if (input[el->i] != el->quote)
	{
		buffer[el->j] = input[el->i];
		el->j++;
	}
	else if (input[el->i] == el->quote && el->i != el->k)
		flag->a = false;
	el->i++;
	if (flag->a == false)
	{
		second_loop(input, buffer, el, flag);
		if (flag->a == false)
		{
			buffer[el->j] = el->quote;
			el->j++;
			if (flag->a == false && input[el->i] != '\0')
			{
				buffer[el->j] = ' ';
				el->j++;
			}
			return (false);
		}
	}
	return (true);
}

static void	logic_loop(char *input, char *buffer, t_elem *el, t_flags *flag)
{
	while (input[el->i] == '<' || input[el->i] == '>' || input[el->i] == '|')
	{
		buffer[el->j] = input[el->i];
		el->j++;
		el->i++;
	}
	el->k = el->i;
	first_loop(input, el, flag);
	if (flag->a)
	{
		buffer[el->j] = el->quote;
		el->j++;
		while (input[el->i])
		{
			if (!check_quote(input, buffer, el, flag))
				break ;
		}
	}
	else if (input[el->i] != el->quote)
	{
		buffer[el->j] = input[el->i];
		el->j++;
	}
	if (input[el->i] != '\0')
		el->i++;
}

char	*deal_with_quotes(char *input)
{
	t_elem	elem;
	t_flags	flag;
	char	*buffer;

	elem.i = 0;
	elem.j = 0;
	elem.quote = 0;
	flag.a = false;
	flag.b = false;
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(input) * 2));
	if (!buffer)
		exit(1);
	ft_bzero(buffer, sizeof(char) * (ft_strlen(input) * 2));
	while (input[elem.i] != '\n' && input[elem.i])
		logic_loop(input, buffer, &elem, &flag);
	if (flag.a == true)
	{
		free(buffer);
		write(2, "Unclosed quotes\n", 16);
		return (NULL);
	}
	return (buffer);
}

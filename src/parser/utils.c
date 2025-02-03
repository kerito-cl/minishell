/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:40:48 by mquero            #+#    #+#             */
/*   Updated: 2025/02/01 15:20:00 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

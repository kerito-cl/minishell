/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:36:52 by mquero            #+#    #+#             */
/*   Updated: 2024/11/08 12:11:49 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*des;

	len = ft_strlen(s);
	des = (char *)malloc((len + 1) * sizeof(char));
	if (des == NULL || s == NULL)
	{
		free(des);
		return (NULL);
	}
	len = 0;
	while (s[len])
	{
		des[len] = s[len];
		len++;
	}
	des[len] = '\0';
	return (des);
}

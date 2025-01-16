/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:40:48 by mquero            #+#    #+#             */
/*   Updated: 2025/01/16 11:19:24 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (dest == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '/';
	i++;
	while (s2[j] != '\0')
	{
		if (s2[j] == ' ')
			break ;
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*des;

	len = ft_strlen(s);
	des = (char *)malloc((len + 1) * sizeof(char));
	if (des == NULL)
		return (NULL);
	len = 0;
	while (s[len])
	{
		des[len] = s[len];
		len++;
	}
	des[len] = '\0';
	return (des);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:40:48 by mquero            #+#    #+#             */
/*   Updated: 2025/01/22 13:53:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strjoin_slash(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*dest;

// 	i = 0;
// 	j = 0;
// 	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
// 	if (dest == NULL)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	dest[i] = '/';
// 	i++;
// 	while (s2[j] != '\0')
// 	{
// 		if (s2[j] == ' ')
// 			break ;
// 		dest[i + j] = s2[j];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// 	return (dest);
// }

char	*ft_strndup(const char *s, size_t n)
{
	size_t		len;
	char	*des;

	len = ft_strlen(s);
	des = (char *)malloc((n + 1) * sizeof(char));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:21:02 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/23 17:52:32 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_array(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	if (count == 0)
	{
		while (arr[count] != NULL)
			count++;
	}
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

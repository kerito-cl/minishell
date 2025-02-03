/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:55 by mquero            #+#    #+#             */
/*   Updated: 2025/02/01 14:02:21 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= len)
	{
		if (tokens[i].cmd)
		{
			j = 0;
			while (tokens[i].cmd[j])
			{
				free(tokens[i].cmd[j]);
				j++;
			}
			free(tokens[i].cmd);
		}
		i++;
	}
	free(tokens);
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->value)
	{
		i = 0;
		while (node->value[i])
			free(node->value[i++]);
		free(node->value);
	}
	free(node);
}

void	exit_free(t_token *tokens, int len, char *buffer)
{
	if (buffer)
		free(buffer);
	free_tokens(tokens, len);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:55 by mquero            #+#    #+#             */
/*   Updated: 2025/02/17 11:18:16 by mquero           ###   ########.fr       */
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
		{
			free(node->value[i++]);
			if (node->fd != -1)
				close(node->fd);
		}
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}

void	exit_free(t_token *tokens, int len, char *buffer)
{
	if (buffer)
		free(buffer);
	if (*tokens[0].root)
		free_ast(*tokens[0].root);
	if (tokens)
		free_tokens(tokens, len);
	exit_destroy_minishell(tokens[0].ms);
	exit(1);
}

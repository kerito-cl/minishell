/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:55 by mquero            #+#    #+#             */
/*   Updated: 2025/01/26 19:45:39 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_tokens(t_token *tokens, int len)
{
    int i;
    int j;

	i = 0;
	j = 0;
    while (i <= len)
    {
        if (tokens[i].cmd)
        {
            while (tokens[i].cmd[j])
			{
                free(tokens[i].cmd[j]);
				j++;
			}
            free(tokens[i].cmd);
        }
        i++;
    }
    free(tokens[i].cmd);
    free(tokens);
}

void free_ast(t_ast *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    if (node->value)
    {
        int i = 0;
        while (node->value[i])
            free(node->value[i++]);
        free(node->value);
    }
    free(node);
}

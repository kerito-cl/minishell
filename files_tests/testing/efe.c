/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:55 by mquero            #+#    #+#             */
/*   Updated: 2025/01/21 19:22:26 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    free_tokens(t_token *tokens, int len)
{
    int i;

    i = 0;
    while (i <= len)
   {
        free(tokens[i].value);
        tokens[i].value = NULL;
        i++;
    }
    free(tokens);
}

void free_ast(t_ast *node) {
    if (node == NULL)
        return;
    free_ast(node->left);
    free_ast(node->right);
    if (node->value != NULL)
        free(node->value);
    free(node);
}

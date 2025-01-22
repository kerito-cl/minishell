/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:28:29 by mquero            #+#    #+#             */
/*   Updated: 2025/01/22 13:53:48 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast* create_node(char *s1 , tokentype type) 
{
    t_ast *new_node;
    size_t  len;

    new_node = (t_ast *)malloc(sizeof(t_ast));
    if (!new_node) 
        exit(1);
    len = 0; 
    if (s1 != NULL)
    {
        len = ft_strlen(s1);
        new_node->value = ft_strndup(s1, len);
    }
    else
        new_node->value = NULL;
    new_node->type = type;
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}

t_ast  *divide_input(t_token *tokens, int len, t_index *i)
{
    t_ast *root;

    while (i->pip > 0)
    {
        if (tokens[i->pip].type == PIPE)
        {
            root = create_node(NULL, PIPE);
            break;
        }
        i->pip--;
    }
    if (i->pip > 0)
    {
        i->max = i->pip;
        i->len = i->pip;
        assign_to_left(root, tokens, i, false);
        i->min = i->pip + 1;
        i->max = len;
        assign_to_right(root, tokens, i);
    }
    else
        find_root(&root, tokens, i);
    return (root);
}

t_ast *parse_input(char *input)
{
    t_index i;
    t_token *tokens;
    t_ast *root;
    int len;

    tokens = (t_token *)malloc(sizeof(t_token) * ft_strlen(input) + 1);
    ft_bzero(tokens, sizeof(t_token) * ft_strlen(input) + 1);
    len = tokenize(tokens, input);
    i.pip = len + 1;
    i.min = 0;
    i.len = len;
    i.max = i.len ;
    root = divide_input(tokens, len, &i);
    free_tokens(tokens, len);
    return (root);
}
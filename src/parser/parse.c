/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:28:29 by mquero            #+#    #+#             */
/*   Updated: 2025/02/05 13:16:30 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_node(char **s1, t_tokentype type, t_token *tokens)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	if (!new_node)
		exit_free(tokens, tokens[0].len, NULL);
	ft_bzero(new_node, sizeof(t_ast));
	if (s1 != NULL)
	{
		new_node->value = cpy_cmds(s1);
		if (!new_node->value)
			exit_free(tokens, tokens[0].len, NULL);
	}
	else
		new_node->value = NULL;
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_ast	*divide_input(t_token *tokens, int len, t_index *i)
{
	t_ast	*root;

	root = NULL;
	tokens[0].root = &root;
	while (i->pip > 0)
	{
		if (tokens[i->pip].type == PIPE)
		{
			root = create_node(NULL, PIPE, tokens);
			break ;
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

t_ast	*parse_input(char *input, char **envp)
{
	t_token	*tokens;
	t_ast	*root;
	t_index	i;
	char	*var;
	int		len;

	var = handle_dollar_sign(input, envp);
	if (!var)
		return (NULL);
	tokens = (t_token *)ft_calloc(sizeof(t_token), ft_strlen(var) * 2);
	if (!tokens)
		exit(1);
	len = tokenize(tokens, var);
	if (!check_parse_error(tokens, len))
		return (NULL);
	if (len == -1)
		return (NULL);
	tokens[0].len = len;
	i.pip = len + 1;
	i.min = 0;
	i.len = len;
	i.max = i.len;
	root = divide_input(tokens, len, &i);
	free_tokens(tokens, len);
	return (root);
}

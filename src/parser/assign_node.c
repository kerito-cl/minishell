/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:54:30 by mquero            #+#    #+#             */
/*   Updated: 2025/02/15 12:48:57 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	assign_pipe(t_ast *root, t_token *tokens, t_index *i)
{
	int		prev_max;

	prev_max = i->max;
	i->key = i->max - 1;
	while (i->key > i->min)
	{
		if (PIPE == tokens[i->key].type)
		{
			root->left = create_node(NULL, PIPE, tokens);
			i->max = i->key;
			assign_to_left(root->left, tokens, i, false);
			i->min = i->max + 1;
			i->max = prev_max;
			assign_to_right(root->left, tokens, i);
			return (true);
		}
		i->key--;
	}
	return (false);
}

bool	assign_node(t_ast **root, t_token *tokens, t_index *i, t_tokentype n)
{
	i->key = i->min;
	i->max = i->max;
	while (i->key < i->max)
	{
		if (n == tokens[i->key].type && !tokens[i->key].lock)
		{
			*root = create_node(tokens[i->key + 1].cmd, n, tokens);
			tokens[i->key].lock = true;
			tokens[i->key + 1].lock = true;
			assign_to_left(*root, tokens, i, true);
			return (true);
		}
		i->key++;
	}
	return (false);
}

void	assign_to_right(t_ast *root, t_token *tokens, t_index *i)
{
	if (assign_node(&(root->right), tokens, i, REIN2))
		return ;
	if (assign_node(&(root->right), tokens, i, REIN))
		return ;
	if (assign_node(&(root->right), tokens, i, REOUT))
		return ;
	if (assign_node(&(root->right), tokens, i, REOUT2))
		return ;
	i->key = i->min;
	i->max = i->max;
	while (i->key <= i->max)
	{
		if (ARG == tokens[i->key].type && !tokens[i->key].lock)
		{
			root->right = create_node(tokens[i->key].cmd, CMD, tokens);
			tokens[i->key].lock = true;
			return ;
		}
		i->key++;
	}
}

void	assign_to_left(t_ast *root, t_token *tokens, t_index *i, bool flag)
{
	if (assign_pipe(root, tokens, i))
		return ;
	if (assign_node(&(root->left), tokens, i, REIN2))
		return ;
	if (assign_node(&(root->left), tokens, i, REIN))
		return ;
	if (assign_node(&(root->left), tokens, i, REOUT))
		return ;
	if (assign_node(&(root->left), tokens, i, REOUT2))
		return ;
	i->key = i->min;
	while (i->key <= i->max)
	{
		if (ARG == tokens[i->key].type && !tokens[i->key].lock)
		{
			if (!flag)
				root->left = create_node(tokens[i->key].cmd, CMD, tokens);
			else
				root->right = create_node(tokens[i->key].cmd, CMD, tokens);
			tokens[i->key].lock = true;
			return ;
		}
		i->key++;
	}
}

void	find_root(t_ast **root, t_token *tokens, t_index *i)
{
	if (assign_node(root, tokens, i, REIN2))
		return ;
	if (assign_node(root, tokens, i, REIN))
		return ;
	if (assign_node(root, tokens, i, REOUT))
		return ;
	if (assign_node(root, tokens, i, REOUT2))
		return ;
	i->key = i->min;
	while (i->key <= i->max)
	{
		if (ARG == tokens[i->key].type && !tokens[i->key].lock)
		{
			*root = create_node(tokens[i->key].cmd, CMD, tokens);
			tokens[i->key].lock = true;
			return ;
		}
		i->key++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:38:32 by athill            #+#    #+#             */
/*   Updated: 2024/04/18 12:02:58 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

static int	reduce(t_buffer *stack)
{
	t_ast	*last;
	t_ast	*node;

	last = buffer_last(stack);
	while (last && last->type != NODE_GROUP_OPEN)
	{
		node = buffer_pop(stack);
		last = buffer_last(stack);
		if (last)
			buffer_push(&last->children, node);
		else
			buffer_push(stack, node);
	}
	return (0);
}

static size_t	parse_leaftok(t_buffer const *tokens, size_t i, t_buffer *stack)
{
	t_ast	*node;
	t_ast	*new_node;

	node = buffer_last(stack);
	new_node = ast_new(NODE_LEAF, tokens->ptr[i]);
	while (++i < tokens->len && !is_meta(((char *)tokens->ptr[i])[0]))
		buffer_push(&new_node->children, tokens->ptr[i]);
	if (!node || node->type == NODE_GROUP_OPEN || i == tokens->len
		|| (ft_streq(tokens->ptr[i], "|") && node->type != NODE_PIPE))
		buffer_push(stack, new_node);
	else
		buffer_push(&node->children, new_node);
	return (i - 1);
}

static int	parse_metatok(char *token, char *next, t_buffer *stack)
{
	t_ast	*node;

	node = buffer_last(stack);
	if (node && node->type == NODE_PIPE && !ft_streq(token, "|"))
		reduce(stack);
	if (ft_streq(token, "(") && node && node->type == NODE_LEAF)
		return (print_err(SYNTAX_ERR, "unexpected token", "("));
	if (ft_streq(token, "("))
		buffer_push(stack, ast_new(NODE_GROUP_OPEN, 0));
	else if (ft_streq(token, ")") && node)
	{
		reduce(stack);
		node = buffer_last(stack);
		if (!node || node->type != NODE_GROUP_OPEN)
			return (print_err(SYNTAX_ERR, "unexpected token", ")"));
		node->type = NODE_GROUP;
		if (stack->len >= 2
			&& ((t_ast *)stack->ptr[stack->len - 2])->type != NODE_GROUP_OPEN
			&& (!next || !ft_streq(next, "|")
				|| ((t_ast *)stack->ptr[stack->len - 2])->type == NODE_PIPE))
		{
			node = buffer_pop(stack);
			buffer_push(&((t_ast *)buffer_last(stack))->children, node);
		}
	}
	else if (ft_streq(token, "||") && node)
		buffer_push(stack, ast_new(NODE_OR, buffer_pop(stack)));
	else if (ft_streq(token, "&&") && node)
		buffer_push(stack, ast_new(NODE_AND, buffer_pop(stack)));
	else if (ft_streq(token, "|") && node)
	{
		if (!node || node->type != NODE_PIPE)
			buffer_push(stack, ast_new(NODE_PIPE, buffer_pop(stack)));
	}
	else
		return (print_err(SYNTAX_ERR, "unexpected token", token));
	return (0);
}

int	ast_parse(t_buffer const *tokens, t_buffer *stack)
{
	size_t	i;
	int		status;
	t_ast	*node;

	buffer_init(stack);
	i = -1;
	status = 0;
	while (++i < tokens->len)
	{
		//printf("tok %s\n", (char *)tokens->ptr[i]);
		if (!is_meta(((char const *)tokens->ptr[i])[0]))
			i = parse_leaftok(tokens, i, stack);
		else if (i + 1 < tokens->len)
			status = parse_metatok(tokens->ptr[i], tokens->ptr[i + 1], stack);
		else
			status = parse_metatok(tokens->ptr[i], 0, stack);
		if (status)
			return (status);
	}
	reduce(stack);
	node = buffer_last(stack);
	if (stack->len > 1 || (node && node->type == NODE_GROUP_OPEN))
		return (print_err(SYNTAX_ERR, 0, "unexpected EOF"));
	return (0);
}

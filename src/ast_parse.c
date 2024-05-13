/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:38:32 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 11:01:18 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if ((node->type == NODE_OR || node->type == NODE_AND
				|| node->type == NODE_PIPE) && node->children.len < 2)
		{
			buffer_push(stack, node);
			return (1);
		}
		if (last)
			buffer_push(&last->children, node);
		else
			buffer_push(stack, node);
	}
	return (0);
}

static int	parse_closing(char const *token, char const *next, t_buffer *stack)
{
	t_ast	*node;
	int		status;

	status = reduce(stack);
	node = buffer_last(stack);
	if (status || node->type != NODE_GROUP_OPEN)
		return (print_syntax_err(NULL, token));
	node->type = NODE_GROUP;
	if (stack->len >= 2
		&& ((t_ast *)stack->ptr[stack->len - 2])->type != NODE_GROUP_OPEN
		&& (!next || !ft_streq(next, "|")
			|| ((t_ast *)stack->ptr[stack->len - 2])->type == NODE_PIPE))
	{
		node = buffer_pop(stack);
		buffer_push(&((t_ast *)buffer_last(stack))->children, node);
	}
	return (status);
}

static int	parse_metatok(char const *token, char const *next, t_buffer *stack)
{
	t_ast	*node;
	int		status;

	status = 0;
	node = buffer_last(stack);
	if (status || (ft_streq(token, "(") && node && node->type == NODE_LEAF))
		return (print_syntax_err(NULL, token));
	if (ft_streq(token, "("))
		buffer_push(stack, ast_new(NODE_GROUP_OPEN, 0));
	else if (ft_streq(token, ")") && node)
		status = parse_closing(token, next, stack);
	else if (ft_streq(token, "||") && node)
		buffer_push(stack, ast_new(NODE_OR, buffer_pop(stack)));
	else if (ft_streq(token, "&&") && node)
		buffer_push(stack, ast_new(NODE_AND, buffer_pop(stack)));
	else if (ft_streq(token, "|") && node)
	{
		if (node->type != NODE_PIPE)
			buffer_push(stack, ast_new(NODE_PIPE, buffer_pop(stack)));
	}
	else
		return (print_syntax_err(NULL, token));
	return (status);
}

int	ast_parse(t_buffer const *tokens, t_buffer *stack)
{
	size_t	i;
	int		status;
	t_ast	*node;

	i = -1;
	status = 0;
	while (++i < tokens->len)
	{
		if (!is_meta(((char const *)tokens->ptr[i])[0])
			|| token_is_redir(tokens->ptr[i]))
			status = parse_leaftok(tokens, &i, stack);
		else if (i + 1 < tokens->len)
			status = parse_metatok(tokens->ptr[i], tokens->ptr[i + 1], stack);
		else
			status = parse_metatok(tokens->ptr[i], NULL, stack);
		if (status)
			return (status);
	}
	if (reduce(stack) || (tokens->len && ft_streq(tokens->ptr[i - 1], "|")))
		return (print_syntax_err(NULL, NULL));
	node = buffer_last(stack);
	if (stack->len > 1 || (node && node->type == NODE_GROUP_OPEN))
		return (print_syntax_err(NULL, NULL));
	return (0);
}

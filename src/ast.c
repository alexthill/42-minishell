/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:00:11 by athill            #+#    #+#             */
/*   Updated: 2024/04/23 12:38:50 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

t_ast	*ast_new(t_node_type type, void *element)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (ast == 0)
		exit(print_errno(1, 0));
	ast->type = type;
	buffer_init(&ast->children);
	buffer_init(&ast->redirs);
	if (element)
		buffer_push(&ast->children, element);
	return (ast);
}

void	ast_free(void *node)
{
	t_ast	*ast;
	size_t	i;

	ast = node;
	i = -1;
	while (++i < ast->redirs.len)
		free(ast->redirs.ptr[i]);
	free(ast->redirs.ptr);
	if (ast->type == NODE_LEAF)
		free(ast->children.ptr);
	else
		buffer_free(&ast->children, &ast_free);
	free(node);
}

static int	continue_token(char const *s, char const *start, char quote)
{
	if (*s == 0)
		return (0);
	if (s == start || quote)
		return (1);
	return (!is_blank(*s) && is_meta(*s) == is_meta(*start)
		&& *s != '(' && *s != ')');
}

int	ast_tokenize(char const *s, t_buffer *tokens)
{
	char const	*start;
	char		quote;

	buffer_init(tokens);
	quote = 0;
	while (1)
	{
		while (is_blank(*s))
			s++;
		if (*s == 0)
			break ;
		start = s;
		while (continue_token(s, start, quote))
		{
			if (*s == quote)
				quote = 0;
			else if (*s == '"' || *s == '\'')
				quote = *s;
			s++;
		}
		buffer_push(tokens, ft_substr2(start, 0, s - start));
		if (buffer_last(tokens) == 0)
			return (print_errno(1, 0));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:51:03 by athill            #+#    #+#             */
/*   Updated: 2024/04/18 11:50:03 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"
#include "buffer.h"
#include "minishell.h"

void	ast_print(t_ast *ast)
{
	size_t	i;

	i = -1;
	if (ast->type == NODE_LEAF)
		printf("[LEAF:");
	else if (ast->type == NODE_AND)
		printf("[&&:");
	else if (ast->type == NODE_OR)
		printf("[||:");
	else if (ast->type == NODE_PIPE)
		printf("[|:");
	else if (ast->type == NODE_GROUP)
		printf("(:");
	else
		printf("[?%i:", ast->type);
	while (++i < ast->children.len)
	{
		printf(" ");
		if (ast->type == NODE_LEAF)
			printf("%s", (char *)ast->children.ptr[i]);
		else
			ast_print(ast->children.ptr[i]);
	}
	if (ast->type == NODE_GROUP)
		printf(")");
	else
		printf("]");
}

int	ast_test(char *s)
{
	t_buffer	tokens;
	t_buffer	stack;
	size_t		i;

	if (ast_tokenize(s, &tokens))
	{
		buffer_free(&tokens, &free);
		return (print_err(1, 0, "failed to tokenize"));
	}
	if (ast_parse(&tokens, &stack))
	{
		buffer_free(&tokens, &free);
		buffer_free(&stack, &ast_free);
		return (print_err(1, 0, "failed to parse"));
	}
	i = -1;
	while (++i < stack.len)
	{
		ast_print(stack.ptr[i]);
		printf("\n");
	}
	buffer_free(&tokens, &free);
	buffer_free(&stack, &ast_free);
	return (0);
}

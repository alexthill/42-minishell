/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:54:25 by athill            #+#    #+#             */
/*   Updated: 2024/04/18 10:58:59 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "buffer.h"

typedef enum e_node_type
{
	NODE_UNKNOWN,
	NODE_LEAF,
	NODE_AND,
	NODE_OR,
	NODE_PIPE,
	NODE_GROUP,
	NODE_GROUP_OPEN,
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	t_buffer		children;
}	t_ast;

t_ast	*ast_new(t_node_type type, void *element);
void	ast_free(void *ast);
int		ast_tokenize(char const *s, t_buffer *tokens);
int		ast_parse(t_buffer const *tokens, t_buffer *stack);

void	ast_print(t_ast *ast);

#endif

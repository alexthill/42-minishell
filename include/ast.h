/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:54:25 by athill            #+#    #+#             */
/*   Updated: 2024/04/19 15:54:56 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "buffer.h"

typedef enum e_node_type
{
	NODE_ROOT,
	NODE_LEAF,
	NODE_AND,
	NODE_OR,
	NODE_PIPE,
	NODE_GROUP,
	NODE_GROUP_OPEN,
	NODE_UNKNOWN,
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	t_buffer		children;
	t_buffer		redirs;
}	t_ast;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
}	t_redir;

t_ast	*ast_new(t_node_type type, void *element);
void	ast_free(void *ast);
int		ast_tokenize(char const *s, t_buffer *tokens);
int		ast_parse(t_buffer const *tokens, t_buffer *stack);
int		token_is_redir(char const *token);
int		ast_parse_redir(t_buffer const *tokens, size_t *i, t_buffer *redirs);

void	ast_print(t_ast *ast);

#endif

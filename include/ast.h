/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:54:25 by athill            #+#    #+#             */
/*   Updated: 2024/05/02 13:43:16 by athill           ###   ########.fr       */
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

// ast.c
t_ast	*ast_new(t_node_type type, void *element);
void	ast_free(void *ast);
int		print_syntax_err(char *prog, char const *token);
int		ast_tokenize(char const *s, t_buffer *tokens, int quote);

// ast_parse.c
int		ast_parse(t_buffer const *tokens, t_buffer *stack);

// ast_leaf.c
int		token_is_redir(char const *token);
int		parse_leaftok(t_buffer const *tokens, size_t *i, t_buffer *stack);

// ast_print.c
void	ast_print(t_ast *ast);

#endif

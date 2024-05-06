/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_leaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:32:03 by athill            #+#    #+#             */
/*   Updated: 2024/05/06 09:14:17 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "buffer.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

static int	ast_parse_redir(t_buffer const *tokens, size_t *i, t_buffer *redirs)
{
	const char		*token = tokens->ptr[*i];
	t_redir			*redir;

	if (*i == tokens->len - 1)
		return (print_syntax_err(NULL, "newline"));
	redir = malloc(sizeof(t_redir));
	if (redir == 0)
		return (print_errno(1, 0));
	if (ft_streq(token, "<"))
		redir->type = REDIR_IN;
	else if (ft_streq(token, "<<"))
		redir->type = REDIR_HEREDOC;
	else if (ft_streq(token, ">"))
		redir->type = REDIR_OUT;
	else if (ft_streq(token, ">>"))
		redir->type = REDIR_APPEND;
	else
		return (print_err(1, "called ast_parse_redir with bad token", token));
	*i = *i + 1;
	redir->file = tokens->ptr[*i];
	buffer_push(redirs, redir);
	if (is_meta(redir->file[0]))
		return (print_syntax_err(NULL, redir->file));
	return (0);
}

int	token_is_redir(char const *token)
{
	return (ft_streq(token, "<") || ft_streq(token, "<<")
		|| ft_streq(token, ">") || ft_streq(token, ">>"));
}

static void	insert_leaf(t_buffer const *tokens, size_t i, t_buffer *stack,
		t_ast *leaf)
{
	t_ast	*node;

	node = buffer_last(stack);
	if (node && node->type == NODE_GROUP && leaf->children.len == 0)
	{
		node->redirs = leaf->redirs;
		free(leaf);
	}
	else if (!node || node->type == NODE_GROUP_OPEN || i == tokens->len
		|| (ft_streq(tokens->ptr[i], "|") && node->type != NODE_PIPE))
		buffer_push(stack, leaf);
	else
		buffer_push(&node->children, leaf);
}

int	parse_leaftok(t_buffer const *tokens, size_t *i, t_buffer *stack)
{
	t_ast	*leaf;
	int		status;

	status = 0;
	leaf = ast_new(NODE_LEAF, 0);
	while (*i < tokens->len && status == 0)
	{
		if (!is_meta(((char const *)tokens->ptr[*i])[0]))
			buffer_push(&leaf->children, tokens->ptr[*i]);
		else if (token_is_redir(tokens->ptr[*i]))
			status = ast_parse_redir(tokens, i, &leaf->redirs);
		else
			break ;
		*i = *i + 1;
	}
	insert_leaf(tokens, *i, stack, leaf);
	*i = *i - 1;
	return (status);
}

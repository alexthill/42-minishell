/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:32:03 by athill            #+#    #+#             */
/*   Updated: 2024/04/19 15:54:48 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "buffer.h"
#include "libft.h"
#include "minishell.h"

int	token_is_redir(char const *token)
{
	return (ft_streq(token, "<") || ft_streq(token, "<<")
		|| ft_streq(token, ">") || ft_streq(token, ">>"));
}

int	ast_parse_redir(t_buffer const *tokens, size_t *i, t_buffer *redirs)
{
	const char		*token = tokens->ptr[*i];
	t_redir			*redir;
	t_redir_type	type;

	if (*i == tokens->len - 1)
		return (print_err(SYNTAX_ERR, "unexpected token", "newline"));
	redir = malloc(sizeof(t_redir));
	if (redir == 0)
		return (print_errno(1, 0));
	if (ft_streq(token, "<"))
		type = REDIR_IN;
	else if (ft_streq(token, "<<"))
		type = REDIR_HEREDOC;
	else if (ft_streq(token, ">"))
		type = REDIR_OUT;
	else if (ft_streq(token, ">>"))
		type = REDIR_APPEND;
	else
		return (print_err(1, "called ast_parse_redir with bad token", token));
	redir->type = type;
	*i = *i + 1;
	redir->file = tokens->ptr[*i];
	buffer_push(redirs, redir);
	return (0);
}

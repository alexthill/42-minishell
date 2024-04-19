/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:17 by athill            #+#    #+#             */
/*   Updated: 2024/04/18 16:13:56 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ast.h"
#include "buffer.h"
#include "builtins.h"
#include "libft.h"
#include "minishell.h"

static void	exec_extern(t_data *data, char **args)
{
	size_t	i;
	char	*path;

	if (args[0][0] == '.' || args[0][0] == '/')
		exit(print_errno(execve(args[0], args, data->envp), args[0]));
	i = -1;
	while (data->path[++i])
	{
		path = path_concat(data->path[i], args[0]);
		execve(path, args, data->envp);
		free(path);
	}
	exit(print_err(CMD_NOT_FOUND, args[0], MSG_CMD_NOT_FOUND));
}

static int	exec_leaf(t_data *data, char **args)
{
	pid_t	pid;
	int		status;

	if (args == 0 || args[0] == 0)
		return (print_err(1, 0, "no args"));
	if (is_builtin(args[0]))
		return (exec_builtin(data, args));
	pid = fork();
	if (pid < 0)
		status = print_errno(1, 0);
	else if (pid)
	{
		if (waitpid(pid, &status, 0) < 0)
			return (print_errno(1, "waitpid"));
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = WTERMSIG(status);
	}
	else
		exec_extern(data, args);
	return (status);
}

static int	exec_and_or(t_data *data, t_ast const *ast)
{
	int	status;

	if (ast->children.len != 2)
		return (print_err(1, 0, "and/or node does not have 2 children"));
	status = exec_ast(data, ast->children.ptr[0]);
	if ((ast->type == NODE_AND && !status) || (ast->type == NODE_OR && status))
		status = exec_ast(data, ast->children.ptr[1]);
	return (status);
}

int	exec_ast(t_data *data, t_ast *ast)
{
	if (ast == 0)
		return (print_err(1, 0, "cannot execute null ast"));
	if (ast->type == NODE_GROUP)
		return (exec_ast(data, buffer_last(&ast->children)));
	if (ast->type == NODE_OR || ast->type == NODE_AND)
		return (exec_and_or(data, ast));
	if (ast->type == NODE_PIPE)
		return (exec_pipe(data, ast));
	if (ast->type == NODE_LEAF)
	{
		buffer_push(&ast->children, 0);
		return (exec_leaf(data, (char **)ast->children.ptr));
	}
	return (print_err(1, 0, "not implemented"));
}

int	exec_line(t_data *data, char const *line)
{
	t_buffer	tokens;
	t_buffer	stack;
	int			status;

	status = ast_tokenize(line, &tokens);
	if (status)
	{
		buffer_free(&tokens, &free);
		return (status);
	}
	status = ast_parse(&tokens, &stack);
	if (status)
	{
		buffer_free(&tokens, &free);
		buffer_free(&stack, &ast_free);
		return (status);
	}
	if (stack.len != 1)
		status = print_err(1, 0, "something went wrong parsing");
	else
		status = exec_ast(data, buffer_last(&stack));
	buffer_free(&tokens, &free);
	buffer_free(&stack, &ast_free);
	return (status);
}

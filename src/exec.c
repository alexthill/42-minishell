/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:17 by athill            #+#    #+#             */
/*   Updated: 2024/04/26 10:04:01 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ast.h"
#include "buffer.h"
#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

static int	exec_extern(t_data *data, char **args)
{
	size_t	i;
	char	*path;
	char	**envp;
	int		status;

	status = env_to_envp(data, &envp);
	if (status)
		return (status);
	if (args[0][0] == '.' || args[0][0] == '/')
	{
		execve(args[0], args, envp);
		ft_str_array_free(envp);
		return (print_errno(1, args[0]));
	}
	i = -1;
	while (data->path[++i])
	{
		path = path_concat(data->path[i], args[0]);
		execve(path, args, envp);
		free(path);
	}
	ft_str_array_free(envp);
	return (print_err(CMD_NOT_FOUND, args[0], MSG_CMD_NOT_FOUND));
}

static int	exec_leaf(t_data *data, t_ast *ast, char **args)
{
	pid_t	pid;
	int		status;

	if (args == 0)
		return (print_err(1, 0, "no args"));
	status = check_redirs(data, &ast->redirs);
	if (status)
		return (status);
	if (is_builtin(args[0]))
		return (exec_builtin(data, args));
	pid = 0;
	if (!data->in_pipe)
		pid = fork();
	if (pid < 0)
		return (print_errno(1, 0));
	if (pid)
		return (wait_for_process(pid));
	status = exec_redirs(data) || exec_extern(data, args);
	free_args(args);
	data_free(data);
	exit(status);
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
	const int	old_in_pipe = data->in_pipe;
	char		**args;
	int			status;

	if (ast == 0)
		return (print_err(1, 0, "cannot execute null ast"));
	status = 1;
	if (ast->type == NODE_GROUP)
	{
		data->in_pipe = 0;
		status = exec_ast(data, buffer_last(&ast->children));
		data->in_pipe = old_in_pipe;
	}
	else if (ast->type == NODE_OR || ast->type == NODE_AND)
		status = exec_and_or(data, ast);
	else if (ast->type == NODE_PIPE)
		status = exec_pipe(data, ast);
	else if (ast->type == NODE_LEAF)
	{
		args = expand_args(data, ast->children.len, (char **)ast->children.ptr);
		status = reset_redirs(data, exec_leaf(data, ast, args));
		free_args(args);
	}
	return (status);
}

int	exec_line(t_data *data, char const *line)
{
	t_buffer	tokens;
	t_buffer	stack;
	int			status;

	status = ast_tokenize(line, &tokens, 0);
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
	if (stack.len == 1)
		status = exec_ast(data, buffer_last(&stack));
	else if (stack.len > 1)
		status = print_err(1, 0, "something went wrong parsing");
	buffer_free(&tokens, &free);
	buffer_free(&stack, &ast_free);
	return (status);
}

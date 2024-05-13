/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:17 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 11:14:02 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "buffer.h"
#include "minishell.h"
#include "utils.h"

static int	exec_group(t_data *data, t_ast *ast)
{
	int			status;
	pid_t		pid;

	if (ast->children.len != 1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (print_errno(1, 0));
	if (pid)
		return (wait_for_process(pid, data));
	signal_default();
	status = exec_redirs(data);
	data->in_pipe = 0;
	data->infile = STDIN_FILENO;
	data->outfile = STDOUT_FILENO;
	if (!status)
		status = exec_ast(data, buffer_last(&ast->children));
	data_free(data);
	exit(status);
}

static int	exec_and_or(t_data *data, t_ast *ast)
{
	int	status;

	if (ast->children.len != 2)
		return (print_err(1, NULL, "and/or ast node has not 2 children"));
	status = exec_ast(data, ast->children.ptr[0]);
	if (get_signum() == SIGINT)
		return (0);
	if ((ast->type == NODE_AND && !status)
		|| (ast->type == NODE_OR && status))
		status = exec_ast(data, ast->children.ptr[1]);
	return (status);
}

int	exec_ast(t_data *data, t_ast *ast)
{
	char		**args;
	int			status;

	status = check_redirs(data, &ast->redirs);
	if (status)
		return (status);
	if (get_signum() == SIGINT)
		(void)"do nothing (yes, this a comment (f*** the norm))";
	else if (ast->type == NODE_GROUP)
		status = exec_group(data, ast);
	else if (ast->type == NODE_OR || ast->type == NODE_AND)
		status = exec_and_or(data, ast);
	else if (ast->type == NODE_PIPE)
		status = exec_pipe(data, ast);
	else if (ast->type == NODE_LEAF)
	{
		args = expand_args(data, ast->children.len, (char **)ast->children.ptr);
		status = exec_leaf(data, args);
		ft_str_array_free(args);
	}
	reset_redirs(data);
	return (status);
}

int	exec_line(t_data *data, char *line)
{
	int			status;

	status = ast_tokenize(line, &data->tokens, 0);
	free(line);
	if (status)
	{
		buffer_free(&data->tokens, &free);
		return (data_set_status(data, status));
	}
	status = ast_parse(&data->tokens, &data->ast_stack);
	if (status)
	{
		buffer_free(&data->tokens, &free);
		buffer_free(&data->ast_stack, &ast_free);
		return (data_set_status(data, status));
	}
	if (data->ast_stack.len == 1)
		data_set_status(data, exec_ast(data, buffer_last(&data->ast_stack)));
	else if (data->ast_stack.len > 1)
		data_set_status(data, print_err(1, 0, "something went wrong parsing"));
	buffer_free(&data->tokens, &free);
	buffer_free(&data->ast_stack, &ast_free);
	return (data->last_status);
}

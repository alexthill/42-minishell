/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:39:06 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 11:31:34 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"
#include "utils.h"

static int	exec_pipe_child(t_data *data, t_ast *ast, size_t i, int link[2])
{
	int	status;

	signal_default();
	if (i != 0)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (i != ast->children.len - 1)
	{
		close(link[0]);
		dup2(link[1], STDOUT_FILENO);
		close(link[1]);
	}
	data->in_pipe = 1;
	status = exec_ast(data, ast->children.ptr[i]);
	data_free(data);
	return (status);
}

static int	exec_pipe_helper(t_data *data, t_ast *ast, pid_t *pids)
{
	int		link[2];
	size_t	i;

	i = -1;
	while (++i < ast->children.len)
	{
		if (i == ast->children.len - 1)
			link[1] = STDOUT_FILENO;
		else if (pipe(link))
			return (print_errno(1, 0));
		pids[i] = fork();
		if (pids[i] < 0)
			return (print_errno(1, 0));
		if (pids[i] == 0)
			(free(pids), exit(exec_pipe_child(data, ast, i, link)));
		if (i != 0)
			close(data->fd_in);
		if (i != ast->children.len - 1)
		{
			data->fd_in = link[0];
			close(link[1]);
		}
	}
	return (0);
}

int	exec_pipe(t_data *data, t_ast *ast)
{
	pid_t	*pids;
	int		status;
	size_t	i;

	pids = ft_calloc(ast->children.len, sizeof(pid_t));
	if (pids == 0)
		return (print_errno(1, 0));
	data->fd_in = data->infile;
	status = exec_pipe_helper(data, ast, pids);
	i = -1;
	while (++i < ast->children.len && pids[i])
		status = wait_for_process(pids[i], data);
	free(pids);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:39:06 by athill            #+#    #+#             */
/*   Updated: 2024/04/22 14:41:47 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ast.h"
#include "minishell.h"
#include "utils.h"

static int	wait_for_children(t_ast *ast, pid_t *pids)
{
	int		status;
	size_t	i;

	i = -1;
	status = 0;
	while (++i < ast->children.len)
		status = wait_for_process(pids[i]);
	free(pids);
	return (status);
}

int	exec_pipe(t_data *data, t_ast *ast)
{
	pid_t	*pids;
	int		link[2];
	size_t	i;
	int		fd_in;

	pids = malloc(ast->children.len * sizeof(pid_t));
	if (pids == 0)
		return (print_errno(1, 0));
	fd_in = data->infile;
	i = -1;
	while (++i < ast->children.len)
	{
		if (i == ast->children.len - 1)
			link[1] = 1;
		else if (pipe(link))
			return (print_errno(1, 0));
		pids[i] = fork();
		if (pids[i] < 0)
			return (print_errno(1, 0));
		if (pids[i] == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (i != ast->children.len - 1)
			{
				close(link[0]);
				dup2(link[1], 1);
				close(link[1]);
			}
			data->in_pipe = 1;
			exit(exec_ast(data, ast->children.ptr[i]));
		}
		if (i != 0)
			close(fd_in);
		if (i != ast->children.len - 1)
		{
			fd_in = link[0];
			close(link[1]);
		}
	}
	return (wait_for_children(ast, pids));
}

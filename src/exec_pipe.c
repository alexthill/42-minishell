/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:39:06 by athill            #+#    #+#             */
/*   Updated: 2024/04/18 16:46:35 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ast.h"
#include "minishell.h"

static int	wait_for_children(t_ast *ast, pid_t *pids)
{
	int		status;
	size_t	i;

	i = -1;
	status = 0;
	while (++i < ast->children.len)
	{
		printf("wait for process %i\n", pids[i]);
		status = 0;
		if (waitpid(pids[i], &status, 0) < 0)
			print_errno(1, "waitpid");
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = WTERMSIG(status);
	}
	free(pids);
	return (status);
}

int	exec_pipe(t_data *data, t_ast *ast)
{
	pid_t	*pids;
	int		link[2];
	size_t	i;
	int		fd_in;

	printf("start pipe of len %li\n", ast->children.len);
	pids = malloc(ast->children.len * sizeof(pid_t));
	if (pids == 0)
		return (print_errno(1, 0));
	fd_in = 0;
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
			//if (i != ast->children.len - 1)
			//	close(link[0]);
			if (i != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (i != ast->children.len - 1)
			{
				dup2(link[1], 1);
				close(link[1]);
			}
			return (exec_ast(data, ast->children.ptr[i]));
		}
		printf("spawned process %i\n", pids[i]);
		if (i != 0)
			close(fd_in);
		if (i != ast->children.len - 1)
			close(link[1]);
	}
	return (wait_for_children(ast, pids));
}

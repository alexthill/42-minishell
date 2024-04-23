/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:41:17 by athill            #+#    #+#             */
/*   Updated: 2024/04/23 09:55:37 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ast.h"
#include "buffer.h"
#include "minishell.h"

static void	handle_redir(t_data *data, t_redir *redir)
{
	int		file_flags;

	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
	{
		if (data->infile != STDIN_FILENO)
			close(data->infile);
		data->infile = open(redir->file, O_RDONLY);
	}
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
	{
		if (data->outfile != STDOUT_FILENO)
			close(data->outfile);
		if (redir->type == REDIR_OUT)
			file_flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			file_flags = O_WRONLY | O_CREAT | O_APPEND;
		data->outfile = open(redir->file, file_flags, 0644);
	}
}

int	check_redirs(t_data *data, t_buffer *redirs)
{
	size_t	i;
	t_redir	*redir;

	i = -1;
	while (++i < redirs->len)
	{
		redir = redirs->ptr[i];
		handle_redir(data, redir);
		if (data->infile < 0 || data->outfile < 0)
			return (print_errno(reset_redirs(data, 1), redir->file));
	}
	return (0);
}

int	exec_redirs(t_data *data)
{
	int		status;

	status = 0;
	if (data->infile != STDIN_FILENO)
	{
		status = dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	if (data->outfile != STDOUT_FILENO)
	{
		if (!status)
			status = dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
	return (print_errno(status < 0, 0));
}

int	reset_redirs(t_data *data, int status)
{
	if (data->infile != STDIN_FILENO)
	{
		if (data->infile != -1)
			close(data->infile);
		data->infile = STDIN_FILENO;
	}
	if (data->outfile != STDOUT_FILENO)
	{
		if (data->outfile != -1)
			close(data->outfile);
		data->outfile = STDOUT_FILENO;
	}
	return (status);
}

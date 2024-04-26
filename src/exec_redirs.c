/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:41:17 by athill            #+#    #+#             */
/*   Updated: 2024/04/26 10:44:18 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "ast.h"
#include "buffer.h"
#include "minishell.h"

static int	read_here_doc(t_data *data, char *limiter)
{
	char	*line;
	char	*expanded;
	int		link[2];

	if (pipe(link) == -1)
		return (-1);
	while (1)
	{
		line = get_line(data, PROMPT_HEREDOC);
		if (line == NULL || ft_streq(line, limiter))
			break ;
		expanded = expand_string(data, line, 0);
		free(line);
		ft_putendl_fd(expanded, link[1]);
		free(expanded);
	}
	if (line == NULL)
		print_err(1, "here-doc delimited by end-of-file, wanted", limiter);
	else
		free(line);
	close(link[1]);
	return (link[0]);
}

static void	handle_redir(t_data *data, t_redir *redir)
{
	int	file_flags;

	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
	{
		if (data->infile != STDIN_FILENO)
			close(data->infile);
		if (redir->type == REDIR_HEREDOC)
			data->infile = read_here_doc(data, redir->file);
		else
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
		redir->file = expand_string(data, redir->file, 1);
		handle_redir(data, redir);
		if (data->infile < 0 || data->outfile < 0)
		{
			print_errno(1, redir->file);
			return (reset_redirs(data, 1));
		}
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

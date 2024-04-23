/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:41:17 by athill            #+#    #+#             */
/*   Updated: 2024/04/23 10:34:40 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ast.h"
#include "buffer.h"
#include "minishell.h"
#include "get_next_line.h"

static int	read_here_doc(char *limiter)
{
	char	*line;
	int		link[2];
	size_t	len;

	if (pipe(link) == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		len = ft_strlen(line);
		if (line == 0 || line[len - 1] != '\n')
		{
			print_err(1, "here-doc delimited by end-of-file, wanted", limiter);
			break ;
		}
		line[len - 1] = '\0';
		if (ft_streq(line, limiter))
			break ;
		line[len - 1] = '\n';
		ft_putstr_fd(line, link[1]);
		free(line);
	}
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
			data->infile = read_here_doc(redir->file);
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

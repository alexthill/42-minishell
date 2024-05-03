/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:41:17 by athill            #+#    #+#             */
/*   Updated: 2024/05/03 13:38:23 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "ast.h"
#include "buffer.h"
#include "minishell.h"

static int	read_here_doc(t_data *data, char const *limiter)
{
	char	*line;
	char	*expanded;
	int		link[2];

	if (pipe(link) == -1)
		return (-1);
	while (1)
	{
		line = get_line(data, PROMPT_HEREDOC);
		if (get_signum() == SIGINT || line == NULL || ft_streq(line, limiter))
			break ;
		expanded = expand_string2(data, line);
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

static int	handle_redir(t_data *data, t_redir_type type, char *file)
{
	int	file_flags;

	if (type == REDIR_IN || type == REDIR_HEREDOC)
	{
		if (data->infile != STDIN_FILENO)
			close(data->infile);
		if (type == REDIR_HEREDOC)
			data->infile = read_here_doc(data, file);
		else
			data->infile = open(file, O_RDONLY);
	}
	else if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		if (data->outfile != STDOUT_FILENO)
			close(data->outfile);
		if (type == REDIR_OUT)
			file_flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			file_flags = O_WRONLY | O_CREAT | O_APPEND;
		data->outfile = open(file, file_flags, 0644);
	}
	if (data->infile == -1 || data->outfile == -1)
		return (print_errno(1, file), free(file), 1);
	return (free(file), 0);
}

int	check_redirs(t_data *data, t_buffer *redirs)
{
	size_t		i;
	t_redir		*redir;
	t_buffer	expanded;
	int			status;

	buffer_init(&expanded);
	i = -1;
	status = 0;
	while (++i < redirs->len && !status)
	{
		redir = redirs->ptr[i];
		expand_string(data, redir->file, &expanded);
		if (expanded.len != 1)
			status = print_err(1, redir->file, "ambiguous redirect");
		else
			status = handle_redir(data, redir->type, buffer_pop(&expanded));
	}
	buffer_free(&expanded, &free);
	if (status)
		reset_redirs(data);
	return (status);
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

void	reset_redirs(t_data *data)
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
}

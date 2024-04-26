/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:59:56 by athill            #+#    #+#             */
/*   Updated: 2024/04/26 09:34:31 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "libft.h"
#include "minishell.h"

static int	matches_pattern(char const *s, char const *p)
{
	if (*s == '.' && *p != '.')
		return (0);
	while (*p)
	{
		if (*p != '*' && *s != *p)
			return (0);
		if (*p != '*' && *s == *p)
		{
			p++;
			s++;
			continue ;
		}
		while (*p == '*')
			p++;
		while (*s && *s != *p)
			s++;
	}
	return (*s == '\0');
}

static int	read_from_dir(DIR *dir, char const *pattern, t_buffer *buf)
{
	struct dirent	*dirent;

	dirent = readdir(dir);
	if (!dirent)
		return (0);
	if (matches_pattern(dirent->d_name, pattern))
	{
		buffer_push(buf, ft_strdup(dirent->d_name));
		if (buffer_last(buf) == NULL)
			exit(print_errno(1, NULL));
	}
	return (1);
}

static int	glob_arg(char *arg, t_buffer *buf)
{
	DIR				*dir;
	const size_t	buf_start = buf->len;

	buffer_push(buf, arg);
	if (!ft_strchr(arg, '*'))
		return (0);
	dir = opendir(".");
	if (dir == NULL)
		return (print_errno(1, NULL));
	buffer_pop(buf);
	while (read_from_dir(dir, arg, buf))
	{
	}
	closedir(dir);
	ft_sort_str_tab((char **)&buf->ptr[buf_start], buf->len - buf_start);
	if (buf_start == buf->len)
		buffer_push(buf, arg);
	else
		free(arg);
	return (0);
}

int	glob_args(char ***args)
{
	size_t		i;
	int			has_glob;
	t_buffer	buf;
	int			status;

	has_glob = 0;
	i = -1;
	while ((*args)[++i])
		has_glob |= ft_strchr((*args)[i], '*') != 0;
	if (!has_glob)
		return (0);
	buffer_init(&buf);
	status = 0;
	i = -1;
	while ((*args)[++i])
		status |= glob_arg((*args)[i], &buf);
	buffer_push(&buf, NULL);
	free(*args);
	*args = (char **)buf.ptr;
	return (status);
}

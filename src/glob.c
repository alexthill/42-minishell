/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:59:56 by athill            #+#    #+#             */
/*   Updated: 2024/04/25 13:21:07 by athill           ###   ########.fr       */
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

static int	glob_arg(char *arg, t_buffer *buf)
{
	DIR				*dir;
	struct dirent	*dirent;
	const size_t	buf_start = buf->len;

	if (!ft_strchr(arg, '*'))
	{
		buffer_push(buf, arg);
		return (0);
	}
	dir = opendir(".");
	if (dir == NULL)
		return (print_errno(1, NULL));
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (matches_pattern(dirent->d_name, arg))
			buffer_push(buf, ft_strdup(dirent->d_name));
	}
	closedir(dir);
	free(arg);
	ft_sort_str_tab((char **)&buf->ptr[buf_start], buf->len - buf_start);
	return (0);
}

int	glob_args(char ***args)
{
	size_t		i;
	int			has_glob;
	t_buffer	buf;

	i = 0;
	has_glob = 0;
	while ((*args)[++i])
		has_glob |= ft_strchr((*args)[i], '*') != 0;
	if (!has_glob)
		return (0);
	buffer_init(&buf);
	buffer_push(&buf, (*args)[0]);
	i = 0;
	while ((*args)[++i])
		glob_arg((*args)[i], &buf);
	buffer_push(&buf, NULL);
	free(*args);
	*args = (char **)buf.ptr;
	return (0);
}

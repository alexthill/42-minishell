/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:59:56 by athill            #+#    #+#             */
/*   Updated: 2024/05/15 10:26:53 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "buffer.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

static int	matches_pattern(char const *s, char const *p)
{
	if (*s == '.' && *p != '.')
		return (0);
	while (*p)
	{
		if (*p == '\\')
			p++;
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

static int	matches_pattern2(char const *s, char const *p)
{
	char const	*end;

	if (*s == '.' && *p != '.')
		return (0);
	while (*p)
	{
		if (*p == '\\')
			p++;
		if (*p != '*' && *s != *p)
			return (0);
		if (*p != '*' && *s == *p && p++ && s++)
			continue ;
		while (*p == '*')
			p++;
		end = s + ft_strlen(s);
		while (s != end && *end != *p)
			end--;
		if (s == end && *s != *p)
			return (0);
		s = end;
	}
	return (*s == '\0');
}

static int	read_from_dir(DIR *dir, char const *pattern, t_buffer *buf)
{
	struct dirent	*dirent;

	dirent = readdir(dir);
	if (!dirent)
		return (0);
	if (matches_pattern(dirent->d_name, pattern)
		|| matches_pattern2(dirent->d_name, pattern))
	{
		buffer_push(buf, ft_strdup(dirent->d_name));
		if (buffer_last(buf) == NULL)
			exit(print_errno(1, NULL));
	}
	return (1);
}

static int	glob_arg_helper(char *arg, t_buffer *buf)
{
	DIR				*dir;
	const size_t	old_len = buf->len;

	buffer_push(buf, arg);
	if (!strchr_escaped(arg, '*', '\\'))
		return (0);
	dir = opendir(".");
	if (dir == NULL)
		return (print_errno(1, NULL));
	buffer_pop(buf);
	while (read_from_dir(dir, arg, buf))
	{
	}
	closedir(dir);
	ft_sort_str_tab((char **)&buf->ptr[old_len], buf->len - old_len);
	if (old_len == buf->len)
		buffer_push(buf, arg);
	else
		free(arg);
	return (0);
}

int	glob_arg(char *arg, t_buffer *buf)
{
	size_t	i;
	int		status;

	i = buf->len - 1;
	status = glob_arg_helper(arg, buf);
	while (++i < buf->len)
		buf->ptr[i] = str_unescape(buf->ptr[i], '\\');
	return (status);
}

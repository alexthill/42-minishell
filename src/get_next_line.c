/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:58:57 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 11:08:06 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int	ft_buffer_realloc(t_gnl_buffer *buf, size_t n)
{
	const size_t	len = buf->len - (buf->start - buf->ptr);
	char			*tmp;

	tmp = 0;
	if (len + n > buf->cap)
	{
		if (n > buf->cap)
			buf->cap += n;
		else
			buf->cap *= 2;
		tmp = buf->ptr;
		buf->ptr = malloc(buf->cap * sizeof(char));
		if (buf->ptr == 0)
			return (1);
	}
	ft_memmove(buf->ptr, buf->start, len);
	free(tmp);
	buf->start = buf->ptr;
	buf->len = len;
	return (0);
}

static char	*find_newline(t_gnl_buffer *buf)
{
	char	*s;

	s = buf->start;
	if (s == 0)
		return (0);
	while (s < buf->ptr + buf->len)
		if (*s++ == '\n')
			return (s);
	return (0);
}

static char	*read_next_line(int fd, t_gnl_buffer *buf)
{
	ssize_t	res;
	char	*end;

	while (1)
	{
		end = find_newline(buf);
		if (end)
			return (end);
		if (ft_buffer_realloc(buf, BUFFER_SIZE))
			return (0);
		res = read(fd, buf->ptr + buf->len, BUFFER_SIZE);
		if (res < 0)
			return (0);
		if (res == 0)
			return (buf->ptr + buf->len);
		buf->len += res;
	}
}

char	*get_next_line(int fd)
{
	static t_gnl_buffer	buf;
	char				*end;
	char				*s;

	end = 0;
	if (BUFFER_SIZE > 0 && fd >= 0)
		end = read_next_line(fd, &buf);
	if (end == 0 || buf.start == end)
	{
		free(buf.ptr);
		buf.ptr = 0;
		buf.start = 0;
		buf.len = 0;
		buf.cap = 0;
		return (0);
	}
	s = malloc((end - buf.start + 1) * sizeof(char));
	if (s == 0)
		return (0);
	ft_memmove(s, buf.start, end - buf.start);
	s[end - buf.start] = '\0';
	buf.start = end;
	return (s);
}

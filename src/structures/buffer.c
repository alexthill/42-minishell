/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:29:18 by athill            #+#    #+#             */
/*   Updated: 2024/04/23 14:17:18 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft.h"

void	buffer_init(t_buffer *buf)
{
	buf->ptr = 0;
	buf->len = 0;
	buf->cap = 0;
}

void	buffer_reserve(t_buffer *buf, size_t n)
{
	void	*old_ptr;

	if (buf->len + n <= buf->cap)
		return ;
	if (buf->cap * 2 >= buf->len + n)
		buf->cap *= 2;
	else
		buf->cap += n;
	old_ptr = buf->ptr;
	buf->ptr = malloc(buf->cap * sizeof(void *));
	if (buf->ptr == 0)
		exit(1);
	ft_memcpy(buf->ptr, old_ptr, buf->len * sizeof(void *));
	free(old_ptr);
}

void	buffer_free(t_buffer *buf, void (*fn_free)(void *))
{
	size_t	i;

	if (buf == 0)
		return ;
	i = -1;
	while (++i < buf->len)
		fn_free(buf->ptr[i]);
	free(buf->ptr);
	buf->ptr = 0;
	buf->len = 0;
	buf->cap = 0;
}

void	buffer_push(t_buffer *buf, void *element)
{
	buffer_reserve(buf, 1);
	buf->ptr[buf->len++] = element;
}

void	*buffer_pop(t_buffer *buf)
{
	if (buf->len)
		return (buf->ptr[--buf->len]);
	return (0);
}

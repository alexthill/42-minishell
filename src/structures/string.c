/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:05:18 by athill            #+#    #+#             */
/*   Updated: 2024/04/30 15:19:21 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_buffer.h"
#include "libft.h"

void	string_init(t_string *buf)
{
	buf->ptr = 0;
	buf->len = 0;
	buf->cap = 0;
}

void	string_reserve(t_string *buf, size_t n)
{
	void	*old_ptr;

	if (buf->len + n <= buf->cap)
		return ;
	if (buf->cap * 2 >= buf->len + n)
		buf->cap *= 2;
	else
		buf->cap += n;
	old_ptr = buf->ptr;
	buf->ptr = malloc(buf->cap * sizeof(char));
	if (buf->ptr == 0)
		exit(1);
	ft_memcpy(buf->ptr, old_ptr, buf->len * sizeof(char));
	free(old_ptr);
}

void	string_free(t_string *buf)
{
	free(buf->ptr);
	buf->ptr = 0;
	buf->len = 0;
	buf->cap = 0;
}

void	string_push(t_string *buf, char c)
{
	string_reserve(buf, 1);
	buf->ptr[buf->len++] = c;
}

void	string_push2(t_string *buf, char c1, char c2)
{
	string_reserve(buf, 2);
	buf->ptr[buf->len++] = c1;
	buf->ptr[buf->len++] = c2;
}

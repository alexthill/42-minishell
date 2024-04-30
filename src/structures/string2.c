/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:00:21 by athill            #+#    #+#             */
/*   Updated: 2024/04/30 15:19:46 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_buffer.h"

void	string_concat(t_string *buf, char const *str)
{
	const size_t	len = ft_strlen(str);

	string_reserve(buf, len);
	ft_memcpy(&buf->ptr[buf->len], str, len);
	buf->len += len;
}

char	*string_to_null_terminated(t_string *str)
{
	string_push(str, '\0');
	return (str->ptr);
}

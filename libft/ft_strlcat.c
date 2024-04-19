/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:20:17 by athill            #+#    #+#             */
/*   Updated: 2024/02/21 09:38:45 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	dst_len;
	size_t	i;

	if (dst == 0 || src == 0)
		return (0);
	dst_len = 0;
	while (dst_len < size && dst[dst_len] != '\0')
		dst_len++;
	i = 0;
	if (dst_len < size)
	{
		while (dst_len < size - i - 1 && src[i] != '\0')
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (dst_len + i);
}

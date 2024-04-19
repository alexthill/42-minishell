/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:16:59 by athill            #+#    #+#             */
/*   Updated: 2024/02/23 10:41:16 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	const size_t	bytes = nmemb * size;
	char			*mem;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (bytes / nmemb != size)
		return (0);
	mem = malloc(bytes);
	if (mem == 0)
		return (0);
	i = 0;
	while (i < bytes)
		mem[i++] = 0;
	return (mem);
}

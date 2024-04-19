/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:07 by athill            #+#    #+#             */
/*   Updated: 2024/02/21 11:22:39 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	const size_t	len = ft_strlen(s);
	size_t			i;
	char			*dst;

	if (s == 0)
		return (0);
	dst = malloc((len + 1) * sizeof(char));
	if (dst == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[len] = '\0';
	return (dst);
}

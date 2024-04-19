/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:44:02 by athill            #+#    #+#             */
/*   Updated: 2024/02/21 11:01:38 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	s1_len = ft_strlen(s1);
	const size_t	s2_len = ft_strlen(s2);
	size_t			i;
	char			*dst;

	if (s1 == 0 || s2 == 0)
		return (0);
	dst = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (dst == 0)
		return (0);
	i = 0;
	while (i < s1_len)
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		dst[s1_len + i] = s2[i];
		i++;
	}
	dst[s1_len + s2_len] = '\0';
	return (dst);
}

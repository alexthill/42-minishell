/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:46:51 by athill            #+#    #+#             */
/*   Updated: 2024/02/21 11:00:03 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*empty_str(void)
{
	char	*s;

	s = malloc(sizeof(char));
	if (s != 0)
		s[0] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*dst;

	s_len = 0;
	while (s[s_len])
		s_len++;
	if (len == 0 || s_len <= start)
		return (empty_str());
	if (s_len - start < len)
		len = s_len - start;
	dst = malloc((len + 1) * sizeof(char));
	if (dst == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

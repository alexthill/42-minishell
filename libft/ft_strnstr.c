/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:04:17 by athill            #+#    #+#             */
/*   Updated: 2024/02/21 16:00:26 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(char const *big, char const *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (big == 0 || little == 0)
		return (0);
	i = 0;
	while (1)
	{
		j = 0;
		while (1)
		{
			if (little[j] == '\0')
				return ((char *)big + i);
			if (big[i + j] == '\0' || i + j >= len)
				return (0);
			if (little[j] != big[i + j])
				break ;
			j++;
		}
		i++;
	}
	return (0);
}

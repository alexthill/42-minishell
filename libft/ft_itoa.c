/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:24:53 by athill            #+#    #+#             */
/*   Updated: 2024/02/20 11:08:21 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	itoa_len(int n)
{
	if (n == 0)
		return (0);
	return (1 + itoa_len(n / 10));
}

static char	*itoa_write(int n, char *dst)
{
	if (n == 0)
		return (dst);
	dst = itoa_write(n / 10, dst);
	*dst = '0' - (n % 10);
	return (dst + 1);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*dst;

	if (n == 0)
		len = 2;
	else if (n > 0)
		len = itoa_len(n) + 1;
	else
		len = itoa_len(n) + 2;
	dst = malloc(len * sizeof(char));
	if (dst == 0)
		return (0);
	if (n == 0)
		dst[0] = '0';
	else if (n > 0)
		itoa_write(-n, dst);
	else
	{
		dst[0] = '-';
		itoa_write(n, dst + 1);
	}
	dst[len - 1] = '\0';
	return (dst);
}

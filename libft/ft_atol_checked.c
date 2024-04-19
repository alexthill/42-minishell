/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_checked.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:59:55 by athill            #+#    #+#             */
/*   Updated: 2024/04/16 10:00:43 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

long	ft_atol_checked(char const *str, int *error)
{
	unsigned long	nbr;
	long			sign;

	nbr = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	*error = *str == '\0';
	while (*str >= '0' && *str <= '9')
	{
		if (nbr * 10 + *str - '0' < nbr)
			*error = 1;
		nbr = nbr * 10 + *str++ - '0';
	}
	if (*str != '\0' || nbr > (unsigned long)LONG_MAX + (sign == -1))
		*error = 1;
	return (sign * nbr);
}

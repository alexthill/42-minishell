/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:02:08 by athill            #+#    #+#             */
/*   Updated: 2024/02/21 14:32:56 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	helper(int n, int fd)
{
	if (n)
	{
		helper(n / 10, fd);
		ft_putchar_fd('0' - (n % 10), fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n > 0)
		helper(-n, fd);
	else
	{
		ft_putchar_fd('-', fd);
		helper(n, fd);
	}
}

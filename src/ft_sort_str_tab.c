/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_str_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:17:10 by athill            #+#    #+#             */
/*   Updated: 2024/04/25 13:25:01 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	ft_sort_str_tab(char **tab, size_t size)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 1;
	while (i < size)
	{
		j = i;
		while (j > 0)
		{
			if (ft_strcmp(tab[j], tab[j - 1]) >= 0)
				break ;
			tmp = tab[j];
			tab[j] = tab[j - 1];
			tab[j - 1] = tmp;
			j--;
		}
		i++;
	}
}

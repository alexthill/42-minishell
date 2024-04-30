/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_str_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:17:10 by athill            #+#    #+#             */
/*   Updated: 2024/04/30 14:24:06 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int	ft_strcmp2(char const *s1, char const *s2)
{
	size_t	i;
	int		diff;

	i = 0;
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	diff = (unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[i]);
	if (diff)
		return (diff);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (ft_isalpha(s1[i]) && ft_isalpha(s2[i])
		&& ft_tolower(s1[i]) == ft_tolower(s2[i]))
	{
		return (s2[i] - s1[i]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
			if (ft_strcmp2(tab[j], tab[j - 1]) >= 0)
				break ;
			tmp = tab[j];
			tab[j] = tab[j - 1];
			tab[j - 1] = tmp;
			j--;
		}
		i++;
	}
}

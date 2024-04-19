/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:36:09 by athill            #+#    #+#             */
/*   Updated: 2024/02/20 10:46:16 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_str_array_free(char **array)
{
	size_t	i;

	if (array == 0)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*ft_substr2(char const *src, size_t start, size_t end)
{
	size_t	i;
	char	*dst;

	dst = malloc((end - start + 1) * sizeof(char));
	if (dst == 0)
		return (0);
	i = start;
	while (src[i] && i < end)
	{
		dst[i - start] = src[i];
		i++;
	}
	dst[i - start] = '\0';
	return (dst);
}

static void	ft_split_helper(const char *s, char c, char **array)
{
	size_t	i;
	size_t	start;
	size_t	str_count;

	i = 0;
	start = 0;
	str_count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i != start)
				array[str_count++] = ft_substr2(s, start, i);
			start = i + 1;
		}
		i++;
	}
	if (i != start)
		array[str_count++] = ft_substr2(s, start, i);
	array[str_count] = 0;
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	str_count;
	char	**array;

	i = 0;
	start = 0;
	str_count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i != start)
				str_count++;
			start = i + 1;
		}
		i++;
	}
	str_count += i != start;
	array = malloc((str_count + 1) * sizeof(char *));
	if (array == 0)
		return (0);
	ft_split_helper(s, c, array);
	return (array);
}

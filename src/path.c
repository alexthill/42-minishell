/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:04:24 by athill            #+#    #+#             */
/*   Updated: 2024/04/17 15:35:34 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**path_extract(char **envp)
{
	char	**splitted;
	char	**path;

	path = 0;
	while (*envp && path == 0)
	{
		splitted = ft_split(*envp, '=');
		if (splitted == 0 || splitted[0] == 0)
		{
			free(splitted);
			return (0);
		}
		if (splitted[1] && ft_streq(splitted[0], "PATH"))
			path = ft_split(splitted[1], ':');
		ft_str_array_free(splitted);
		envp = &envp[1];
	}
	if (path != 0)
		return (path);
	path = malloc(sizeof(char *));
	if (path != 0)
		path[0] = 0;
	return (path);
}

char	*path_concat(char *p1, char *p2)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(p1, "/");
	if (s1 == 0)
		return (0);
	s2 = ft_strjoin(s1, p2);
	free(s1);
	return (s2);
}

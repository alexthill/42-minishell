/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:04:24 by athill            #+#    #+#             */
/*   Updated: 2024/05/06 14:49:38 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "buffer.h"
#include "libft.h"
#include "minishell.h"

int	path_is_empty(t_data *data)
{
	char const	*value = get_env_var(data, "PATH");

	return (value == NULL || value[0] == '\0');
}

static char	**path_check_emty_segment(char **path, char const *value)
{
	size_t		path_count;
	size_t		colon_count;
	size_t		i;
	t_buffer	buf;

	if (path == NULL)
		return (NULL);
	path_count = 0;
	while (path[path_count])
		path_count++;
	colon_count = 0;
	i = -1;
	while (value[++i])
		if (value[i] == ':')
			colon_count++;
	if (path_count == colon_count + 1)
		return (path);
	buffer_init(&buf);
	i = -1;
	while (path[++i])
		buffer_push(&buf, path[i]);
	buffer_push(&buf, ft_strdup("."));
	buffer_push(&buf, NULL);
	free(path);
	return ((char **)buf.ptr);
}

char	**path_get(t_data *data)
{
	char const	*value = get_env_var(data, "PATH");
	char		**path;

	if (value != NULL && value[0] != '\0')
		return (path_check_emty_segment(ft_split(value, ':'), value));
	path = ft_calloc(2, sizeof(char *));
	if (path == NULL)
		return (NULL);
	path[0] = ft_strdup("");
	if (path[0] != NULL)
		return (path);
	free(path);
	return (NULL);
}

char	*path_concat(char const *p1, char const *p2)
{
	char	*s1;
	char	*s2;

	if (p1 == NULL || p2 == NULL)
		return (NULL);
	if (p1[0] == '\0')
		s1 = ft_strjoin(p1, "./");
	else
		s1 = ft_strjoin(p1, "/");
	if (s1 == NULL)
		return (NULL);
	s2 = ft_strjoin(s1, p2);
	free(s1);
	return (s2);
}

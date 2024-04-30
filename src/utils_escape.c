/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_escape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:57:06 by athill            #+#    #+#             */
/*   Updated: 2024/04/30 15:11:49 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_buffer.h"

char	*str_escape(char *s, char c, char const *escape)
{
	t_string	str;

	string_init(&str);
	while (*s)
	{
		if (*s == c || ft_strchr(escape, *s))
			string_push(&str, c);
		string_push(&str, *s);
		s++;
	}
	return (string_to_null_terminated(&str));
}

char	*str_unescape(char *s, char c)
{
	t_string	str;
	char		*p;

	p = s;
	string_init(&str);
	while (*s)
	{
		if (*s == c && *(s + 1))
			s++;
		string_push(&str, *s);
		s++;
	}
	free(p);
	return (string_to_null_terminated(&str));
}

char const	*strchr_escaped(char const *s, char c, char escape_char)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != escape_char && *s == c)
			return (s);
		if (*s == escape_char)
		{
			s++;
			if (*s == '\0')
				break ;
			if (c == escape_char && *s == escape_char)
				return (s);
		}
		s++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:39:47 by athill            #+#    #+#             */
/*   Updated: 2024/05/06 09:26:19 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "buffer.h"
#include "minishell.h"
#include "string_buffer.h"
#include "utils.h"

static int	expand_return_status(t_data *data, t_string *str)
{
	char	*s;

	s = ft_itoa(data->last_status);
	if (s == 0)
		exit(print_errno(1, 0));
	string_concat_and_free(str, s);
	return (1);
}

static int	expand_var(t_data *data, char const *s, t_string *str, char *escape)
{
	char	*name;
	char	*value;
	size_t	i;

	if (s[0] == '?')
		return (expand_return_status(data, str));
	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (i == 0)
		return (string_push(str, '$'), 0);
	name = ft_substr(s, 0, i);
	if (name == 0)
		exit(print_errno(1, 0));
	value = get_env_var(data, name);
	if (value && escape)
		string_concat_and_free(str, str_escape(value, '\\', escape));
	else if (value)
		string_concat(str, value);
	free(name);
	return (i);
}

char	*expand_string2(t_data *data, char const *s)
{
	t_string	str;

	string_init(&str);
	while (*s)
	{
		if (*s == '$')
			s += expand_var(data, s + 1, &str, NULL);
		else
			string_push(&str, *s);
		s++;
	}
	return (string_to_null_terminated(&str));
}

void	expand_string(t_data *data, char const *s, t_buffer *buf)
{
	char		quote;
	int			has_quote;
	t_string	str;

	string_init(&str);
	quote = 0;
	has_quote = 0;
	while (*s)
	{
		if (*s == quote)
			quote = 0;
		else if (!quote && (*s == '"' || *s == '\'') && ++has_quote)
			quote = *s;
		else if (*s == '$' && !quote)
			s += expand_var(data, s + 1, &str, "");
		else if (*s == '$' && quote == '"')
			s += expand_var(data, s + 1, &str, "*");
		else if (*s == '\\' || (*s == '*' && quote))
			string_push2(&str, '\\', *s);
		else
			string_push(&str, *s);
		s++;
	}
	if (str.len || has_quote)
		glob_arg(string_to_null_terminated(&str), buf);
}

char	**expand_args(t_data *data, size_t argc, char **argv)
{
	t_buffer	buf;
	size_t		i;

	if (argc == 0)
		return (NULL);
	buffer_init(&buf);
	i = -1;
	while (++i < argc)
		expand_string(data, argv[i], &buf);
	buffer_push(&buf, NULL);
	return ((char **)buf.ptr);
}

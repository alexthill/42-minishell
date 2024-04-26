/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:39:47 by athill            #+#    #+#             */
/*   Updated: 2024/04/26 09:26:11 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "string_buffer.h"

static int	expand_return_status(t_data *data, t_string *buf)
{
	char	*s;

	s = ft_itoa(data->last_status);
	if (s == 0)
		exit(print_errno(1, 0));
	string_concat(buf, s);
	return (1);
}

static int	expand_var(t_data *data, char const *s, t_string *buf)
{
	char	*name;
	char	*value;
	size_t	i;

	if (s[0] == '?')
		return (expand_return_status(data, buf));
	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (i == 0)
		string_push(buf, '$');
	else
	{
		name = ft_substr(s, 0, i);
		if (name == 0)
			exit(print_errno(1, 0));
		value = get_env_var(data, name);
		if (value)
			string_concat(buf, value);
		free(name);
	}
	return (i);
}

char	*expand_string(t_data *data, char const *s, int	handle_quotes)
{
	char		quote;
	t_string	buf;

	string_init(&buf);
	quote = 0;
	while (*s)
	{
		if (*s == quote)
			quote = 0;
		else if (handle_quotes && !quote && (*s == '"' || *s == '\''))
			quote = *s;
		else if (*s == '$' && quote != '\'')
			s += expand_var(data, s + 1, &buf);
		else
			string_push(&buf, *s);
		s++;
	}
	string_push(&buf, '\0');
	return (buf.ptr);
}

char	**expand_args(t_data *data, size_t argc, char **argv)
{
	char	**args;
	size_t	i;

	if (argc == 0)
		return (0);
	args = malloc((argc + 1) * sizeof(char *));
	if (args == 0)
		return (0);
	i = -1;
	while (++i < argc)
		args[i] = expand_string(data, argv[i], 1);
	args[i] = 0;
	glob_args(&args);
	return (args);
}

void	free_args(char **args)
{
	size_t	i;

	if (args == 0)
		return ;
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

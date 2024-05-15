/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:43 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/15 09:48:40 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_env_var(t_data *data, char const *name)
{
	t_env	*node;

	if (data == NULL || data->env == NULL)
		return (NULL);
	node = data->env;
	while (node)
	{
		if (node->name != NULL && ft_streq(node->name, name))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

static int	update_directory(t_data *data, char **args, const char *name)
{
	char	*curr;

	curr = getcwd(NULL, 0);
	if (curr == NULL)
		return (print_err(1, ft_strjoin("cd: ", args[1]), MSG_FILE_NOT_FOUND));
	modify_or_add_env_variable(data, ft_strdup(name), curr);
	return (0);
}

int	cmd_cd(t_data *data, char **args)
{
	char	*path;

	if (args[1] == 0)
		path = get_env_var(data, "HOME");
	else if (args[2] != 0)
		return (print_err(1, "cd", MSG_TOO_MANY_ARGS));
	else if (args[1][0] == '\0')
		return (1);
	else
		path = args[1];
	if (update_directory(data, args, "OLDPWD") == 1)
		return (1);
	if (chdir(path) == -1)
		return (print_err_more(data, "cd: ", args[1], MSG_FILE_NOT_FOUND));
	if (update_directory(data, args, "PWD") == 1)
		return (1);
	return (0);
}

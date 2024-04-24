/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:43 by elo               #+#    #+#             */
/*   Updated: 2024/04/24 14:56:57 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_env_var(t_data *data, char *name)
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

int	set_env_var(t_data *data, char *name, char *value)
{
	t_env	*node;
	char	*new_value;

	if (name == NULL || data == NULL || value == NULL)
		return (1);
	node = data->env;
	while (node)
	{
		if (ft_streq(node->name, name))
		{
			new_value = ft_strdup(value);
			if (new_value == NULL)
				return (1);
			free(node->value);
			node->value = new_value;
			return (0);
		}
		node = node->next;
	}
	return (1);
}

int	cmd_cd(t_data *data, char **args)
{
	char	*oldpwd;
	char	*path;
	char	*curr;

	if (args[1] == 0)
		path = get_env_var(data, "HOME");
	else
		path = args[1];
	if (chdir(path) == -1)
		return (print_errno(1, "MSG_CD_ERR"));
	oldpwd = get_env_var(data, "PWD");
	if (oldpwd == NULL)
		return (print_errno(1, "MSG_CD_ERR"));
	if (set_env_var(data, "OLDPWD", oldpwd) == 1)
	{
		free(oldpwd);
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	curr = getcwd(NULL, 0);
	if (curr == NULL)
		return (print_errno(1, "MSG_CD_ERR"));
	if (set_env_var(data, "PWD", curr) == 1)
	{
		free(curr);
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	free(curr);
	return (0);
}

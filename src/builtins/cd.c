/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:43 by elo               #+#    #+#             */
/*   Updated: 2024/04/23 11:08:10 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_env_var(t_data *data, char *name)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (ft_streq(node->name, name))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

int	set_env_var(t_data *data, char *name, char *value)
{
	t_env	*node;

	if (name == NULL || data == NULL || value == NULL)
		return (1);
	node = data->env;
	while (node)
	{
		if (ft_streq(node->name, name))
		{
			free(node->value);
			node->value = ft_strdup(value);
			return (0);
		}
		node = node->next;
	}
	return (1);
}

int	cmd_cd(char **args, t_data *data)
{
	char *oldpwd;
	char *path;

	oldpwd = get_env_var(data, "PWD");
	if (oldpwd == NULL)
	{
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	if (args[1] == 0)
		path = get_env_var(data, "HOME");
	else
		path = args[1];

	if (chdir(path) == -1)
	{
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	if (set_env_var(data, "OLDPWD", oldpwd) == 1)
	{
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	if (set_env_var(data, "PWD", path) == 1)
	{
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	return (0);
}
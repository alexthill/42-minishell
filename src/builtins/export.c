/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:42:56 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/24 15:55:11 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	modify_or_add_env_variable(t_data *data, char *name, char *value)
{
	t_env	*node;

	if (data == NULL || data->env == NULL)
		return (0);
	node = data->env;
	while (node)
	{
		if (node->name != NULL && ft_streq(node->name, name))
		{
			free(node->value);
			node->value = value;
			return (0);
		}
		node = node->next;
	}
	ft_lstadd_front2(&data->env, ft_lstnew2(name, value));
	return (0);
}

int	sort_export(t_data *data)
{
	t_env	*node;
	char	*tmp_name;
	char	*tmp_value;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		node = data->env;
		while (node->next != NULL)
		{
			if (ft_strcmp(node->name, node->next->name) > 0)
			{
				tmp_name = node->name;
				tmp_value = node->value;
				node->value = node->next->value;
				node->name = node->next->name;
				node->next->name = tmp_name;
				node->next->value = tmp_value;
				swap = 1;
			}
			node = node->next;
		}
	}
	return (0);
}

int	print_export(t_data *data)
{
	t_env	*node;

	node = data->env;
	sort_export(data);
	while (node)
	{
		printf("declare -x %s=\"%s\"\n", node->name, node->value);
		node = node->next;
	}
	return (0);
}

int	cmd_export(t_data *data, char **args)
{
	char	*name;
	char	*value;
	char	**splitted;

	if (args[1] != 0)
	{
		splitted = ft_split2(args[1], '=');
		if (splitted == 0 || splitted[0] == 0)
			return (free(splitted), 0);
		name = ft_strdup(splitted[0]);
		if (splitted[1] != NULL)
			value = ft_strdup(splitted[1]);
		else
			value = "";
		free(splitted);
		if (name == NULL || value == NULL)
		{
			free(name);
			free(value);
			return (0);
		}
		modify_or_add_env_variable(data, name, value);
	}
	else
		print_export(data);
	return (0);
}

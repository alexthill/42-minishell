/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:00:17 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/24 17:27:30 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	print_env(t_data *data)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
	return (0);
}

int	cmd_env(t_data *data, char **args)
{
	char	**splitted;
	char	*name;
	char	*value;
	int		i;

	i = 1;
	if (args[1] == 0)
		print_env(data);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			splitted = ft_split2(args[1], '=');
			if (splitted == 0 || splitted[0] == 0)
				return (free(splitted), 0);
			name = ft_strdup(splitted[0]);
			if (splitted[1] != NULL)
				value = ft_strdup(splitted[1]);
			else
				value = 0;
			free(splitted);
			if (name == NULL || value == NULL)
			{
				free(name);
				free(value);
				return (0);
			}
			modify_or_add_env_variable(data, name, value);
		}
		i++;
	}
	return (0);
}

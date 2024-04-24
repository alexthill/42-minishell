/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:07:51 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/24 16:47:28 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	remove_env(t_data *data, char *name)
{
	t_env	*node;
	t_env	*prev;

	node = data->env;
	if (ft_streq(node->name, name))
		data->env = node->next;
	else
	{
		prev = node;
		node = node->next;
		while (node != NULL && !ft_streq(node->name, name))
		{
			prev = node;
			node = node->next;
		}
	}
	if (node == NULL)
		return (0);
	prev->next = node->next;
	free(node->name);
	free(node->value);
	free(node);
	return (0);
}

int	cmd_unset(t_data *data, char **args)
{
	char	*name;
	int		i;

	i = 1;
	name = args[i];
	if (args[i] == 0)
		return (0);
	while (args[i])
	{
		name = args[i];
		remove_env(data, name);
		i++;
	}
	return (0);
}

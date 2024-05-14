/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:07:51 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/14 14:30:14 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	remove_env(t_data *data, char *name)
{
	t_env	*node;
	t_env	*prev;

	node = data->env;
	prev = node;
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
		return ;
	prev->next = node->next;
	free(node->name);
	free(node->value);
	free(node);
	return ;
}

int	cmd_unset(t_data *data, char **args)
{
	int	i;

	if (data->env == NULL)
		return (0);
	i = 1;
	while (args[i])
	{
		remove_env(data, args[i]);
		i++;
	}
	return (0);
}

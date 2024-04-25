/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:00:17 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/25 09:32:36 by ehamm            ###   ########.fr       */
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
	if (args[1] == 0)
		print_env(data);
	return (0);
}

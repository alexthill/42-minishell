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

static void	print_env(t_data *data)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (node->name)
			ft_putstr_fd(node->name, data->outfile);
		ft_putstr_fd("=", data->outfile);
		if (node->value)
			ft_putstr_fd(node->value, data->outfile);
		ft_putchar_fd('\n', data->outfile);
		node = node->next;
	}
}

int	cmd_env(t_data *data, char **args)
{
	if (args[1] == 0)
		print_env(data);
	return (0);
}

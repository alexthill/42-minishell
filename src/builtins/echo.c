/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:11:48 by elo               #+#    #+#             */
/*   Updated: 2024/04/22 16:39:06 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	cmd_echo(t_data *data, char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && ft_streq(args[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], data->outfile);
		i++;
		if (args[i])
			ft_putchar_fd(' ', data->outfile);
	}
	if (newline)
		ft_putchar_fd('\n', data->outfile);
	return (0);
}

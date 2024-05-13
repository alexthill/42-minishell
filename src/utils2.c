/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:37:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/13 18:37:41 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_char_exp(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_isdigit(args[i][0]))
				return (1);
			if (args[i][0] == '=')
				return (1);
			if (args[i][j] == '-')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	count_arg(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
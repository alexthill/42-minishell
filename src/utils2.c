/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:37:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/14 16:42:56 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char_exp(t_data *data, char **args)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	status = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][0] && !ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			status = print_export_err(data, args[i]);
			continue ;
		}
		while (args[i][j] && args[i][j] != '='
			&& (ft_isalnum(args[i][j]) || args[i][j] == '_'))
			j++;
		if (args[i][j] && args[i][j] != '='
			&& !ft_isalnum(args[i][j]) && args[i][j] != '_')
			status = print_export_err(data, args[i]);
	}
	return (status);
}

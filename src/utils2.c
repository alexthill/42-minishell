/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:37:03 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/14 15:02:31 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char_exp(t_data *data, char **args,int i)
{
	int	j;
	char **tmp;
	(void)data;

	i = 0;
	while (args[i])
	{
		tmp = ft_split2(args[i], '=');
		j = 0;
		if (!ft_isalpha(tmp[0][0]) && tmp[0][0] != '_')
			print_err_more(data, ft_strjoin("export: `", args[i]), "'", MSG_EXPORT_ERR);
		while (tmp[0][j])
		{
			if (!ft_isalnum(tmp[0][j]) && tmp[0][j] != '_' && tmp[0][j])
				return (print_err_more(data, ft_strjoin("export: `", args[i]), "'", MSG_EXPORT_ERR));
			j++;
		}
		i++;
	}
	return (0);
}

int	count_arg(char **args)
{
	int count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
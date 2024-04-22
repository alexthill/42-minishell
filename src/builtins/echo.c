/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:11:48 by elo               #+#    #+#             */
/*   Updated: 2024/04/19 18:59:27 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	cmd_echo(char **args)
{
	int 	i;
	int 	newline;

	i = 1;
	newline = 1; // by default we want a new line
	while(args[i] && ft_streq(args[i],"-n"))
	{
		if(ft_streq(args[i],"-n")) // it compares the string with "-n"
			newline = 0;
		else
			break;
		i++;
	}
	while(args[i])
	{
		ft_putstr_fd(args[i],1);
		i++;
		if(args[i]) // if there is another argument
			ft_putchar_fd(' ',1);
	}
	if(newline)
		ft_putchar_fd('\n',1);
	return (1);
}

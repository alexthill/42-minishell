/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:44:05 by athill            #+#    #+#             */
/*   Updated: 2024/04/16 16:43:46 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	cmd_exit(t_data *data, char **args)
{
	int		error;
	long	status;
	char	*s;

	error = 0;
	if (args[1] == 0)
		status = 0;
	else if (args[2] == 0)
		status = ft_atol_checked(args[1], &error);
	else
	{
		status = print_err(TOO_MANY_ARGS, "exit", MSG_TOO_MANY_ARGS);
		error = 2;
	}
	if (error == 1)
	{
		s = ft_strjoin("exit: ", args[1]);
		status = print_err(NUM_ARG_REQUIRED, s, MSG_NUM_ARG_REQUIRED);
		free(s);
	}
	if (error != 2)
		data->exit = 1;
	return (status);
}

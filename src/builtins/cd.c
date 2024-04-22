/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:43 by elo               #+#    #+#             */
/*   Updated: 2024/04/22 10:15:33 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	cmd_cd(t_data *data, char **args)
{
	char *path;
	data->path = &path;

	if (args[1] == 0)
		path = getenv("HOME");
	if (path == 0)
	{
		print_err_full(data->prog, 0, "MSG_CD_ERR");
		return (1);
	}
	else
		path = args[1];    
	if (chdir(path) == -1)
	{
		print_err_full(data->prog, 0, "MSG_CD_ERR");
		return (1);
	}
	return (0);
}
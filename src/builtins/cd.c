/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:43 by elo               #+#    #+#             */
/*   Updated: 2024/04/19 19:04:29 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int	cmd_cd(t_data *data,char **args)
{
	char *path;
	data->path = &path;

	if (args[1] == 0)
		path= getenv("HOME");//getenv returns the value of the environment variable name
		if(path == 0)
		{
			print_err_full(data->prog, 0, "MSG_CD_ERR");
			return (1);
		}
	else
		path = args[1];//if there is an argument, it is the path
	if (chdir(path) == -1)//chdir changes the current working directory of the calling process to the directory specified in path
	{
		print_err_full(data->prog, 0, "MSG_CD_ERR");
		return (1);
	}
	return (0);
}
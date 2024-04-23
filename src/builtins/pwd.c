/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:30:29 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/23 18:02:05 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	cmd_pwd(t_data *data, char **args)
{
	char	*pwd;

	if (args[1] != NULL)
	{
		print_errno(0, "MSG_PWD_ERR");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_errno(0, "MSG_PWD_ERR");
		return (1);
	}
	ft_putstr_fd(pwd, data->outfile);
	ft_putstr_fd("\n", data->outfile);
	free(pwd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:43 by elo               #+#    #+#             */
/*   Updated: 2024/04/22 17:11:12 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_env_data(char *var)
{
	t_env		*tmp;
	size_t		len;

	tmp = NULL;
	len = ft_strlen(var);
	while (tmp)
	{
		if (!(ft_strncmp(var, tmp->name, len)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
// WIP
int	cmd_cd(char **args)
{
	char *pwd;
	char *oldpwd;
	char *path;
	pwd = get_env_data("PWD");
	oldpwd = get_env_data("OLDPWD");

	if (args[1] == 0)
		path = get_env_data("HOME");
	if (path == 0)
	{
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		print_errno(0, "MSG_CD_ERR");
		return (1);
	}
	else
		ft_strlcpy(oldpwd, pwd, ft_strlen(pwd));
	return (0);
}
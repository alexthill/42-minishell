/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:09:43 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/14 15:41:38 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_env_var(t_data *data, char *name)
{
	t_env	*node;

	if (data == NULL || data->env == NULL)
		return (NULL);
	node = data->env;
	while (node)
	{
		if (node->name != NULL && ft_streq(node->name, name))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

int	set_env_var(t_data *data, char *name, char *value)
{
	t_env	*node;
	char	*new_value;

	if (name == NULL || data == NULL || value == NULL)
		return (1);
	node = data->env;
	while (node)
	{
		if (ft_streq(node->name, name))
		{
			new_value = ft_strdup(value);
			if (new_value == NULL)
				return (1);
			free(node->value);
			node->value = new_value;
			return (0);
		}
		node = node->next;
	}
	return (1);
}

static int	update_oldpwd(t_data *data, char **args)
{
	char	*oldpwd;

	oldpwd = get_env_var(data, "PWD");
	if (oldpwd == NULL)
		return (print_err(1, ft_strjoin("cd: ", args[1]), MSG_FILE_NOT_FOUND));
	if (set_env_var(data, "OLDPWD", oldpwd) == 1)
	{
		free(oldpwd);
		print_err(1, ft_strjoin("cd: ", args[1]), MSG_FILE_NOT_FOUND);
		return (1);
	}
	return (0);
}

static int	update_pwd(t_data *data, char **args)
{
	char	*curr;
	int		res;

	curr = getcwd(NULL, 0);
	if (curr == NULL)
		return (print_err(1, ft_strjoin("cd: ", args[1]), MSG_FILE_NOT_FOUND));
	res = set_env_var(data, "PWD", curr);
	free(curr);
	if (res == 1)
	{
		free(curr);
		print_err(1, ft_strjoin("cd: ", args[1]), MSG_FILE_NOT_FOUND);
		return (1);
	}
	return (0);
}

int	cmd_cd(t_data *data, char **args)
{
	char	*path;

	if (count_arg(args) > 2)
		return (print_err(1, "cd", MSG_TOO_MANY_ARGS));
	if (args[1] == 0)
		path = get_env_var(data, "HOME");
	else if (args[1][0] == '\0')
		return (1);
	else if (ft_streq(args[1], "-") == 1)
	{
		path = get_env_var(data, "OLDPWD");
		ft_putstr_fd(path, data->outfile);
		ft_putstr_fd("\n", data->outfile);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
		return (print_err_more(data, "cd: ", args[1], MSG_FILE_NOT_FOUND));
	if (update_oldpwd(data, args) == 1)
		return (1);
	if (update_pwd(data, args) == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:42:56 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/14 15:03:27 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "utils.h"

static void	modify_or_add_env_variable(t_data *data, char *name, char *value)
{
	t_env	*node;

	if (data == NULL || data->env == NULL)
		return ;
	node = data->env;
	while (node)
	{
		if (node->name != NULL && ft_streq(node->name, name))
		{
			free(name);
			free(node->value);
			node->value = value;
			return ;
		}
		node = node->next;
	}
	ft_lstadd_front2(&data->env, ft_lstnew2(name, value));
	return ;
}

static void	swap_nodes(t_env *node)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = node->name;
	tmp_value = node->value;
	node->name = node->next->name;
	node->value = node->next->value;
	node->next->name = tmp_name;
	node->next->value = tmp_value;
}

static int	sort_export(t_data *data)
{
	t_env	*node;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		node = data->env;
		while (node->next != NULL)
		{
			if (ft_strcmp(node->name, node->next->name) > 0)
			{
				swap_nodes(node);
				swap = 1;
			}
			node = node->next;
		}
	}
	return (0);
}

static int	print_export(t_data *data)
{
	t_env	*node;
	char	*escaped;

	sort_export(data);
	node = data->env;
	while (node)
	{
		ft_putstr_fd("declare -x ", data->outfile);
		ft_putstr_fd(node->name, data->outfile);
		if (node->value)
		{
			ft_putstr_fd("=\"", data->outfile);
			escaped = str_escape(node->value, '\\', "\"");
			if (escaped)
				ft_putstr_fd(escaped, data->outfile);
			free(escaped);
			ft_putstr_fd("\"", data->outfile);
		}
		ft_putchar_fd('\n', data->outfile);
		node = node->next;
	}
	return (0);
}

int	cmd_export(t_data *data, char **args, int i)
{
	char	*name;
	char	*value;
	char	**splitted;

	if (is_valid_char_exp(data,args,i) == 1)
		return (print_err_more(data, ft_strjoin("export: `", args[i]), "'",
				MSG_EXPORT_ERR));
	if (args[1] != 0)
	{
		splitted = ft_split2(args[1], '=');
		if (splitted == 0 || splitted[0] == 0)
			return (free(splitted), 0);
		name = splitted[0];
		value = splitted[1];
		free(splitted);
		modify_or_add_env_variable(data, name, value);
	}
	else
		print_export(data);
	return (0);
}

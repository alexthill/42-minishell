/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:00:00 by athill            #+#    #+#             */
/*   Updated: 2024/04/25 10:53:49 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

int	data_init(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	data->prog = argv[0];
	data->envp = envp;
	data->path = path_extract(envp);
	data->is_tty = isatty(STDIN_FILENO);
	data->exit = 0;
	data->in_pipe = 0;
	data->last_status = 0;
	data->infile = STDIN_FILENO;
	data->outfile = STDOUT_FILENO;
	print_err_full(data->prog, 0, 0);
	print_syntax_err(data->prog, 0);
	if (data->path == 0)
		return (print_errno(1, 0));
	data->env = env_var_extract(envp);
	if (data->env == NULL)
	{
		free(data);
		return (print_errno(1, 0));
	}
	return (0);
}

int	data_free(t_data *data)
{
	t_env	*node;

	ft_str_array_free(data->path);
	data->path = 0;
	while (data->env)
	{
		node = data->env;
		free(node->name);
		free(node->value);
		data->env = node->next;
		free(node);
	}
	return (0);
}

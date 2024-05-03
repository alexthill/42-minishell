/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:57:32 by athill            #+#    #+#             */
/*   Updated: 2024/05/03 14:10:15 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "minishell.h"
#include "utils.h"

static int	exec_extern(t_data *data, char **args)
{
	size_t	i;
	char	*path;
	char	**envp;
	int		status;

	status = env_to_envp(data, &envp);
	if (status)
		return (status);
	if (args[0][0] == '.' || args[0][0] == '/')
	{
		execve(args[0], args, envp);
		ft_str_array_free(envp);
		return (translate_errno(print_errno(1, args[0])));
	}
	i = -1;
	while (data->path[++i])
	{
		path = path_concat(data->path[i], args[0]);
		execve(path, args, envp);
		free(path);
	}
	ft_str_array_free(envp);
	return (print_err(CMD_NOT_FOUND, args[0], MSG_CMD_NOT_FOUND));
}

int	exec_leaf(t_data *data, char **args)
{
	pid_t	pid;
	int		status;

	if (!args || !args[0])
		return (0);
	if (is_builtin(args[0]))
		return (exec_builtin(data, args));
	pid = 0;
	if (!data->in_pipe)
		pid = fork();
	if (pid < 0)
		return (print_errno(1, 0));
	if (pid)
		return (wait_for_process(pid, data));
	signal_default();
	status = exec_redirs(data);
	if (!status)
		status = exec_extern(data, args);
	ft_str_array_free(args);
	data_free(data);
	exit(status);
}

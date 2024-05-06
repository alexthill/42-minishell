/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_leaf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:57:32 by athill            #+#    #+#             */
/*   Updated: 2024/05/06 15:49:15 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "minishell.h"
#include "utils.h"

static int	exec_check_path(t_data *data, char **args, char **envp)
{
	char	**path_parts;
	char	*path;
	size_t	i;

	path_parts = path_get(data);
	if (path_parts == NULL)
		return (-1);
	i = -1;
	while (path_parts[++i])
	{
		path = path_concat(path_parts[i], args[0]);
		if (path && access(path, F_OK) == 0)
		{
			execve(path, args, envp);
			free(path);
			ft_str_array_free(path_parts);
			return (translate_errno(print_errno(1, args[0])));
		}
		free(path);
	}
	ft_str_array_free(path_parts);
	if (path_is_empty(data))
		return (print_err(FILE_NOT_FOUND, args[0], MSG_FILE_NOT_FOUND));
	return (print_err(CMD_NOT_FOUND, args[0], MSG_CMD_NOT_FOUND));
}

static int	exec_extern(t_data *data, char **args)
{
	char	**envp;
	int		status;

	status = env_to_envp(data, &envp);
	if (status)
		return (status);
	if (args[0][0] == '.' || args[0][0] == '/')
	{
		execve(args[0], args, envp);
		status = translate_errno(print_errno(1, args[0]));
	}
	else
		status = exec_check_path(data, args, envp);
	ft_str_array_free(envp);
	return (status);
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

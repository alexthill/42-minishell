/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:11 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 18:37:50 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"

int	exec_builtin(t_data *data, char **args)
{
	if (ft_streq(args[0], "exit"))
		return (cmd_exit(data, args));
	else if (ft_streq(args[0], "echo"))
		return (cmd_echo(data, args));
	else if (ft_streq(args[0], "cd"))
		return (cmd_cd(data, args));
	else if (ft_streq(args[0], "pwd"))
		return (cmd_pwd(data, args));
	else if (ft_streq(args[0], "export"))
		return (cmd_export(data, args));
	else if (ft_streq(args[0], "unset"))
		return (cmd_unset(data, args));
	else if (ft_streq(args[0], "env"))
		return (cmd_env(data, args));
	return (0);
}

int	is_builtin(char const *name)
{
	return (ft_streq(name, "exit") || ft_streq(name, "cd") || ft_streq(name,
			"echo") || ft_streq(name, "pwd") || ft_streq(name, "export")
		|| ft_streq(name, "unset") || ft_streq(name, "env"));
}

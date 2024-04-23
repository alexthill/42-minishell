/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:11 by athill            #+#    #+#             */
/*   Updated: 2024/04/23 17:27:32 by ehamm            ###   ########.fr       */
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
	return (0);
}

int	is_builtin(char const *name)
{
	return (ft_streq(name, "exit") || ft_streq(name, "cd") || ft_streq(name,
			"echo"));
}

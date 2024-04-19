/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:11 by athill            #+#    #+#             */
/*   Updated: 2024/04/18 13:42:28 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "builtins.h"

int	exec_builtin(t_data *data, char **args)
{
	if (ft_streq(args[0], "exit"))
		return (cmd_exit(data, args));
	return (0);
}

int	is_builtin(char const *name)
{
	return (ft_streq(name, "exit"));
}

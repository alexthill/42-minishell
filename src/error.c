/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:03:48 by athill            #+#    #+#             */
/*   Updated: 2024/04/29 09:47:35 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <string.h>

int	print_err(int code, char const *s, char const *msg)
{
	if (code)
		print_err_full(0, s, msg);
	return (code);
}

int	print_errno(int is_err, char const *s)
{
	if (is_err)
		return (print_err_full(0, s, 0));
	return (0);
}

int	print_err_full(char *prog, char const *extra, char const *msg)
{
	static char	*prog_name;

	if (prog)
	{
		prog_name = prog;
		return (0);
	}
	ft_putstr_fd(prog_name, 2);
	ft_putstr_fd(": ", 2);
	if (extra)
	{
		ft_putstr_fd(extra, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putendl_fd("", 2);
	return (errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:03:48 by athill            #+#    #+#             */
/*   Updated: 2024/05/14 16:00:23 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

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

int	print_err_more(t_data *prog, char *ext, char *ext2, char *msg)
{
	ft_putstr_fd(prog->prog, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (ext)
		ft_putstr_fd(ext, STDERR_FILENO);
	if (ext2)
	{
		ft_putstr_fd(ext2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

int	print_export_err(t_data *prog, char const *msg)
{
	ft_putstr_fd(prog->prog, STDERR_FILENO);
	if (msg)
	{
		ft_putstr_fd(": export: `", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier", STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}

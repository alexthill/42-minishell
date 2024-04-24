/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:57:41 by athill            #+#    #+#             */
/*   Updated: 2024/04/22 09:25:03 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

void	fn_do_nothing(void *ptr)
{
	(void)ptr;
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_meta(char c)
{
	return (is_blank(c) || c == '\n' || c == '|' || c == '&' || c == '('
		|| c == ')' || c == '<' || c == '>');
}

int	wait_for_process(pid_t	pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (print_errno(1, "waitpid"));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

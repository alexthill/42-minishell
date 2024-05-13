/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:57:41 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 18:03:33 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_meta(char c)
{
	return (is_blank(c) || c == '\n' || c == '|' || c == '&' || c == '('
		|| c == ')' || c == '<' || c == '>');
}

int	wait_for_process(pid_t pid, t_data *data)
{
	int	status;

	(void)data;
	if (waitpid(pid, &status, 0) < 0)
		return (print_errno(1, "waitpid"));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

int	translate_errno(int err)
{
	if (err == 2)
		return (127);
	if (err == 13)
		return (126);
	return (err);
}

int	is_invalid_char_exp(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_isdigit(args[i][0]))
				return (1);
			if (args[i][0] == '=')
				return (1);
			if (args[i][j] == '-')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	count_arg(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}


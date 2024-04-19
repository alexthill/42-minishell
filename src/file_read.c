/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:56:22 by athill            #+#    #+#             */
/*   Updated: 2024/03/25 09:12:56 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

int	stdin_reader(char *limiter)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid > 0)
		return (pid);
	while (1)
	{
		line = get_next_line(0);
	}
	return (0);
}

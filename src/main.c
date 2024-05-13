/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:30:00 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 11:13:47 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"

static int	g_signum = 0;

void	set_signum(int signum)
{
	g_signum = signum;
}

int	get_signum(void)
{
	return (g_signum);
}

char	*get_line(t_data *data, char const *prompt)
{
	char	*line;
	size_t	len;

	if (data->is_tty)
	{
		signal_init(0, 1);
		set_signum(0);
		line = readline(prompt);
		signal_init(0, 0);
		return (line);
	}
	line = get_next_line(STDIN_FILENO);
	len = ft_strlen(line);
	if (line && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*line;

	if (data_init(&data, argc, argv, envp))
		return (1);
	if (data.is_tty)
		signal_init(1, 0);
	line = 0;
	while (data.exit == 0)
	{
		line = get_line(&data, PROMPT);
		if (!line)
			break ;
		if (data.is_tty)
			add_history(line);
		exec_line(&data, line);
		if (get_signum() == SIGINT)
			data.last_status = INTERRUPTED;
	}
	if (data.is_tty)
		ft_putendl_fd("exit", STDOUT_FILENO);
	data_free(&data);
	return (data.last_status);
}

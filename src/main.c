/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:30:00 by athill            #+#    #+#             */
/*   Updated: 2024/04/18 14:06:48 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"

int	ast_test(char *s);

static char	*get_line(t_data *data)
{
	char	*line;

	if (data->is_tty)
		return (readline(PROMPT));
	line = get_next_line(STDIN_FILENO);
	if (line && *line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*line;

	if (data_init(&data, argc, argv, envp))
		return (1);
	line = 0;
	while (data.exit == 0)
	{
		free(line);
		line = get_line(&data);
		if (!line)
			break ;
		if (line[0] == '\0')
			continue ;
		//ast_test(line);
		data.last_status = exec_line(&data, line);
		if (data.is_tty)
			add_history(line);
	}
	free(line);
	data_free(&data);
	return (data.last_status);
}

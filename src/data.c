/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:00:00 by athill            #+#    #+#             */
/*   Updated: 2024/05/15 09:47:37 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "buffer.h"
#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"

static int	update_shlvl(t_data *data)
{
	char	*value;
	char	*new_value;

	value = get_env_var(data, "SHLVL");
	if (!value)
		value = "0";
	new_value = ft_itoa(ft_atoi(value) + 1);
	if (!new_value)
		return (1);
	modify_or_add_env_variable(data, ft_strdup("SHLVL"), new_value);
	return (0);
}

int	data_init(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	data->prog = argv[0];
	data->envp = envp;
	data->is_tty = isatty(STDIN_FILENO);
	data->exit = 0;
	data->in_pipe = 0;
	data->last_status = 0;
	data->infile = STDIN_FILENO;
	data->outfile = STDOUT_FILENO;
	data->env = env_var_extract(envp);
	data->signum = 0;
	buffer_init(&data->tokens);
	buffer_init(&data->ast_stack);
	print_err_full(data->prog, 0, 0);
	print_syntax_err(data->prog, 0);
	if (data->env == NULL || update_shlvl(data))
		return (print_errno(1, 0));
	return (0);
}

int	data_free(t_data *data)
{
	t_env	*node;

	get_next_line(-1);
	buffer_free(&data->tokens, &free);
	buffer_free(&data->ast_stack, &ast_free);
	while (data->env)
	{
		node = data->env;
		free(node->name);
		free(node->value);
		data->env = node->next;
		free(node);
	}
	return (0);
}

int	data_set_status(t_data *data, int status)
{
	data->last_status = status;
	return (status);
}

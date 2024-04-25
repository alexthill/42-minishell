/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:28:31 by athill            #+#    #+#             */
/*   Updated: 2024/04/25 08:39:13 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static size_t	env_size(t_env *env)
{
	size_t	i;

	i = 0;
	while (env && ++i)
		env = env->next;
	return (i);
}

int	env_to_envp(t_data *data, char ***envp)
{
	size_t	i;
	t_env	*node;
	char	*s1;
	char	*s2;

	*envp = ft_calloc(env_size(data->env) + 1, sizeof(char *));
	if (*envp == NULL)
		return (print_errno(1, NULL));
	i = 0;
	node = data->env;
	while (node)
	{
		s1 = ft_strjoin(node->name, "=");
		if (s1 == NULL)
			return (print_errno(1, NULL));
		s2 = ft_strjoin(s1, node->value);
		free(s1);
		if (s2 == NULL)
			return (print_errno(1, NULL));
		(*envp)[i] = s2;
		node = node->next;
		i++;
	}
	return (0);
}

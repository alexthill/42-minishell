/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:19:01 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/15 09:51:47 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstadd_front2(t_env **lst, t_env *new)
{
	if (new == NULL || lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

t_env	*ft_lstnew2(void *name, void *value)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (lst == 0)
		return (0);
	lst->next = 0;
	lst->name = name;
	lst->value = value;
	return (lst);
}

static void	ft_split_helper2(const char *s, char c, char **array)
{
	size_t	i;
	size_t	str_count;

	i = 0;
	str_count = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			str_count = 2;
			array[0] = ft_substr2(s, 0, i);
			array[1] = ft_substr2(s, i + 1, ft_strlen(s));
			break ;
		}
		i++;
	}
	if (str_count == 1)
		array[0] = ft_substr2(s, 0, ft_strlen(s));
	array[str_count] = 0;
}

char	**ft_split2(const char *s, char c)
{
	size_t	i;
	size_t	str_count;
	char	**array;

	i = 0;
	str_count = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			str_count = 2;
			break ;
		}
		i++;
	}
	array = malloc((str_count + 1) * sizeof(char *));
	if (array == 0)
		return (0);
	ft_split_helper2(s, c, array);
	return (array);
}

t_env	*env_var_extract(char **envp)
{
	char	**splitted;
	t_env	*var;
	t_env	*env;

	env = 0;
	while (*envp)
	{
		splitted = ft_split2(*envp, '=');
		if (splitted == 0 || splitted[0] == 0)
		{
			free(splitted);
			return (0);
		}
		var = ft_lstnew2(splitted[0], splitted[1]);
		if (var == NULL)
		{
			free(splitted);
			return (0);
		}
		ft_lstadd_front2(&env, var);
		free(splitted);
		envp++;
	}
	return (env);
}

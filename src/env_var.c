/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:19:01 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/22 14:05:40 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

t_list *env_var_extract(char **envp)
{
	char	**splitted;
	t_envvar	*var;
	t_list	 *env;
	
	env = 0;
	while (*envp)
	{
		splitted = ft_split2(*envp, '=');
		if (splitted == 0 || splitted[0] == 0)
		{
			free(splitted);
			return (0);
		}
		var = malloc(sizeof(t_envvar));
		var->name = splitted[0];
		var->value = splitted[1];
		free(splitted);
		ft_lstadd_front(&env,ft_lstnew(var));
	}
	return (env);
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
			array[0] = ft_substr2(s,0,i);
			array[1] = ft_substr2(s,i+1,ft_strlen(s));
			break;
		}
		i++;
	}
	if(str_count == 1)
		array[0] = ft_substr2(s,0,ft_strlen(s));
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
			break;
		}
		i++;
	}
	array = malloc((str_count + 1) * sizeof(char *));
	if (array == 0)
		return (0);
	ft_split_helper(s, c, array);
	return (array);
}
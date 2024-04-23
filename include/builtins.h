/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:31 by athill            #+#    #+#             */
/*   Updated: 2024/04/23 11:07:03 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		exec_builtin(t_data *data, char **args);
int		is_builtin(char const *name);

int		cmd_exit(t_data *data, char **args);
int		cmd_echo(t_data *data, char **args);
int		cmd_cd(t_data *data, char **args);


//cd.c
char	*get_env_var(t_data *data, char *name);
int		set_env_var(t_data *data, char *name,char *value);
char	**ft_split2(const char *s, char c);

#endif

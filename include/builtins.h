/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:31 by athill            #+#    #+#             */
/*   Updated: 2024/05/13 17:56:15 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		exec_builtin(t_data *data, char **args);
int		is_builtin(char const *name);

int		cmd_cd(t_data *data, char **args);
int		cmd_echo(t_data *data, char **args);
int		cmd_env(t_data *data, char **args);
int		cmd_exit(t_data *data, char **args);
int		cmd_export(t_data *data, char **args);
int		cmd_pwd(t_data *data, char **args);
int		cmd_unset(t_data *data, char **args);

#endif

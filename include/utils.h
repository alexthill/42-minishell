/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:58:42 by athill            #+#    #+#             */
/*   Updated: 2024/05/02 15:49:31 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void		fn_do_nothing(void *ptr);
int			is_blank(char c);
int			is_meta(char c);
int			wait_for_process(pid_t pid, t_data *data);
int			translate_errno(int err);

// utils_escape.c
char		*str_escape(char *s, char c, char const *escape);
char		*str_unescape(char *s, char c);
char const	*strchr_escaped(char const *s, char c, char escape_char);

#endif

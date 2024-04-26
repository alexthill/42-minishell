/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:58:42 by athill            #+#    #+#             */
/*   Updated: 2024/04/26 11:30:23 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	fn_do_nothing(void *ptr);
int		is_blank(char c);
int		is_meta(char c);
int		wait_for_process(pid_t	pid);
int		translate_errno(int err);

#endif

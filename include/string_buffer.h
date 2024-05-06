/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_buffer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:05:31 by athill            #+#    #+#             */
/*   Updated: 2024/05/06 09:03:49 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_BUFFER_H
# define STRING_BUFFER_H

# include <stdlib.h>

typedef struct s_string
{
	char	*ptr;
	size_t	len;
	size_t	cap;
}	t_string;

void	string_init(t_string *buf);
void	string_reserve(t_string *buf, size_t n);
void	string_free(t_string *buf);
void	string_push(t_string *buf, char c);
void	string_push2(t_string *buf, char c1, char c2);

void	string_concat(t_string *buf, char const *s);
void	string_concat_and_free(t_string *buf, char *s);
char	*string_to_null_terminated(t_string *str);

#endif

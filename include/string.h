/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:05:31 by athill            #+#    #+#             */
/*   Updated: 2024/04/23 13:18:15 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

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
void	string_concat(t_string *buf, char const *s);

#endif

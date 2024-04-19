/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:23:31 by athill            #+#    #+#             */
/*   Updated: 2024/04/16 08:56:44 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <stdlib.h>

typedef struct s_buffer
{
	void	**ptr;
	size_t	len;
	size_t	cap;
}	t_buffer;

void	buffer_init(t_buffer *buf);
void	buffer_reserve(t_buffer *buf, size_t n);
void	buffer_free(t_buffer *buf, void (*fn_free)(void *));
void	buffer_push(t_buffer *buf, void *element);
void	*buffer_pop(t_buffer *buf);

void	*buffer_last(t_buffer *buf);

#endif

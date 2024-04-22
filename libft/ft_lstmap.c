/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:26:02 by athill            #+#    #+#             */
/*   Updated: 2024/02/20 15:42:54 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*next;

	if (lst)
	{
		next = 0;
		if (lst->next)
		{
			next = ft_lstmap(lst->next, f, del);
			if (next == 0)
				return (0);
		}
		new = malloc(sizeof(t_list));
		if (new == 0)
		{
			ft_lstclear(&lst, del);
			return (0);
		}
		new->next = next;
		new->content = f(lst->content);
		return (new);
	}
	return (0);
}

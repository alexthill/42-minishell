/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:56:22 by athill            #+#    #+#             */
/*   Updated: 2024/02/20 15:03:43 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	helper(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		helper(lst->next, del);
		ft_lstdelone(lst, del);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	helper(*lst, del);
	*lst = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:12:58 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/29 09:50:52 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>

void	signal_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int sign_num)
{
	if (sign_num == SIGINT)
		printf("\nminishell> ");
	else if (sign_num == SIGQUIT)
	{
		printf("\nexit ");
		exit(1);
	}
	else
		return ;
}

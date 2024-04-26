/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:12:58 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/25 11:35:26 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>

//only needed if we want to send signal manually
//not sure we need it as function signal()is doing it
/*int	send_signal(siginfo_t *info, int sign_num)
{
	if (sign_num == SIGINT)
		if (kill(info->si_pid), SIGINT == -1)
			return (1);
	else if (sign_num == SIGQUIT)
		if (kill(info->si_pid, SIGQUIT) == -1)
			return (1);
	return (0);
}*/
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
		return;
}

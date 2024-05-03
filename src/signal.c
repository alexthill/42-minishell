/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:12:58 by ehamm             #+#    #+#             */
/*   Updated: 2024/05/03 14:23:19 by athill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include "libft.h"
#include "minishell.h"

static void	signal_handler_read(int signum)
{
	set_signum(signum);
	if (signum == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

static void	signal_handler(int signum)
{
	set_signum(signum);
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_init(int init, int for_readline)
{
	struct sigaction	act;
	struct termios		term;

	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	if (init)
	{
		tcgetattr(1, &term);
		term.c_lflag |= ICANON;
		term.c_lflag |= ECHOCTL;
		tcsetattr(1, TCSAFLUSH, &term);
		act.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &act, NULL);
	}
	if (for_readline)
		act.sa_handler = signal_handler_read;
	else
		act.sa_handler = signal_handler;
	sigaction(SIGINT, &act, NULL);
}

void	signal_default(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}

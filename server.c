/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:00:14 by mzary             #+#    #+#             */
/*   Updated: 2024/12/18 14:11:49 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_byte	g_byte;

static void	respond(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid != g_byte.last_cpid)
	{
		g_byte.byte = 0;
		g_byte.bit = 0;
	}
	g_byte.last_cpid = info->si_pid;
	g_byte.byte = (g_byte.byte << 1) | (sig == SIGUSR1);
	g_byte.bit += 1;
	if (g_byte.bit == 8)
	{
		g_byte.bit = 0;
		ft_putchar_fd(g_byte.byte, STDOUT_FILENO);
	}
}

static void	print_server_info(void)
{
	ft_putstr_fd("< server started with process id: [", STDOUT_FILENO);
	ft_putnbr_fd((int)getpid(), STDOUT_FILENO);
	ft_putstr_fd("] >\n", STDOUT_FILENO);
}

int	main(void)
{
	struct sigaction	action;

	action.sa_sigaction = respond;
	sigemptyset(&(action.sa_mask));
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	print_server_info();
	while (1)
		pause();
}

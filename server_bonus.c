/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:00:14 by mzary             #+#    #+#             */
/*   Updated: 2024/12/18 14:51:01 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
		if (g_byte.byte == 0 && kill(g_byte.last_cpid, SIGUSR1) == -1)
		{
			ft_putendl_fd("[error acknowledging message...]", STDOUT_FILENO);
			exit(EXIT_FAILURE);
		}
		else
			ft_putchar_fd(g_byte.byte, STDOUT_FILENO);
		g_byte.bit = 0;
	}
}

static void	print_server_info(void)
{
	ft_putstr_fd("[server started with process id: (", STDOUT_FILENO);
	ft_putnbr_fd((int)getpid(), STDOUT_FILENO);
	ft_putendl_fd(")...]", STDOUT_FILENO);
}

int	main(void)
{
	struct sigaction	sa_s;

	sa_s.sa_sigaction = respond;
	sigemptyset(&(sa_s.sa_mask));
	sa_s.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa_s, NULL);
	sigaction(SIGUSR2, &sa_s, NULL);
	print_server_info();
	while (1)
		pause();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:13:08 by ael-mejd          #+#    #+#             */
/*   Updated: 2024/05/14 00:42:51 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_putnbr(int n)
{
	char c;

	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n >= 0 && n <= 9)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void handler(int sig, siginfo_t *info, void *ctx)
{
	static unsigned char c;
	static int i;

	(void)ctx;
	c |= (sig == SIGUSR1);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(info->si_pid, SIGUSR1);
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int main(void)
{
	int pid;
	struct sigaction sa;

	pid = getpid();
	write(1, "PID :", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	sa.sa_sigaction = &handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

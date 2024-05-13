/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:18:10 by ael-mejd          #+#    #+#             */
/*   Updated: 2024/05/14 00:30:20 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void print_error(char *str)
{
	int i;

	i = 0;
	write(2, "Error : ", 9);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}

int ft_atoi(char *str)
{
	int i;
	long res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > 2147483647)
			print_error("kbar men max int\n");
		i++;
	}
	if (str[i] != '\0')
		print_error("kayn chi 7arf f PID lli dakhalty\n");
	return ((int)res * sign);
}

void handler(int sign)
{
	if (sign == SIGUSR1)
		write(1, "Message bien ressu\n", 20);
}

void send_bit(int pid, unsigned char c)
{
	unsigned char byte;
	int i;

	i = 7;
	while (i >= 0)
	{
		byte = (c >> i) & 1;
		if (byte == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(1337);
		i--;
	}
}

int main(int ac, char **av)
{
	int pid;
	int i;

	i = 0;
	if (ac != 3)
		print_error("Invalid arguments\n");
	signal(SIGUSR1, handler);
	pid = ft_atoi(av[1]);
	if (pid == -1 || pid == 0)
		print_error("Invalid PID\n");
	while (av[2][i])
	{
		send_bit(pid, (unsigned char)av[2][i]);
		usleep(1337);
		i++;
	}
	send_bit(pid, '\0');
	return (0);
}

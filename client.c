/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:22:54 by reldahli          #+#    #+#             */
/*   Updated: 2024/06/24 17:36:21 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ******************************************************************** */
/* The (send_message) function sends each bit of a character			*/
/* to a process identified by pid.										*/
/* The (ft_atoi) function converts a string to an integer				*/
/* The (message_finished) function handles a signal to					*/
/* indicate successful message delivery.								*/
/* The (main) function sets up signal handlers, converts arguments		*/
/* to appropriate types, and sends the message to the specified process.*/
/* (sa_message) Structure for setting up signal handling				*/
/* (error code 4) means there was an issue with							*/
/* configuring the signal handling "SIGUSR1" or the						*/
/* program did not receive the expected number of arguments.			*/
/* (error code 5) means there was a specific issue with					*/
/* configuring the signal handler for SIGUSR2.							*/
/* ******************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void	send_message(char c, int pid)
{
	int	bit_index;

	bit_index = 0;
	while (bit_index < 8)
	{
		if (c & (1 << bit_index))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit_index++;
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	message_finished(int sagnum)
{
	if (sagnum == SIGUSR2)
		write(1, "Message sent successfully.\n", 27);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	sa_message;

	if (argc == 3)
	{
		sa_message.sa_handler = message_finished;
		if (sigaction(SIGUSR1, &sa_message, NULL) == -1)
			return (4);
		if (sigaction(SIGUSR2, &sa_message, NULL) == -1)
			return (5);
		pid = ft_atoi(argv[1]);
		i = 0;
		while (argv[2][i])
		{
			send_message(argv[2][i], pid);
			i++;
		}
		send_message ('\n', pid);
		send_message ('\0', pid);
		return (0);
	}
	else
		write(1, "Wrong input!\n", 13);
	return (4);
}
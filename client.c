#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	reverse_string(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = strlen(str) - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

char	*decimal_to_binary(int num, char *binary)
{
	int	i;

	if (num == 0)
	{
		strcpy(binary, "0");
		return (binary);
	}
	i = 0;
	while (num > 0)
	{
		binary[i] = (num % 2) + '0';
		num = num / 2;
		i++;
	}
	// If the number is less than 7 bits, add 0s to the left
	if (num == 0)
	{
		while (i < 7)
		{
			binary[i] = '0';
			i++;
		}
	}
	binary[i] = '\0';
	// Reverse the string to get the correct binary representation
	reverse_string(binary);
	return (binary);
}

void	send_finished_message(int receiver_pid)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		kill(receiver_pid, SIGUSR2);
		i++;
		usleep(50);
	}
}

int	main(int ac, char *av[])
{
	int		receiver_pid;
	char	*message;
	int		i;
	char	buffer[8];
	char	*binary;
	int		j;

	if (ac != 3)
	{
		printf("Usage: %s <receiver_pid> <message>\n", av[0]);
		return (1);
	}
	receiver_pid = atoi(av[2]);
	message = av[1];
	printf("Sending message to receiver with PID: %d\n", receiver_pid);
	;
	printf("Message sent\n");
	i = 0;
	while (message[i] != '\0')
	{
		binary = decimal_to_binary(message[i], buffer);
		j = 0;
		while (binary[j] != '\0')
		{
			if (binary[j] == '0')
			{
				kill(receiver_pid, SIGUSR2);
			}
			else
			{
				kill(receiver_pid, SIGUSR1);
			}
			j++;
			usleep(50);
		}
		i++;
	}
	send_finished_message(receiver_pid);
	return (0);
}

// H in binary is 1001000
// 127 in binary is  1111111
// 128 in binary is 10000000

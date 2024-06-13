#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	binary_to_decimal(char *binary)
{
	int	decimal;
	int	length;

	decimal = 0;
	length = strlen(binary);
	for (int i = 0; i < length; i++)
	{
		if (binary[length - 1 - i] == '1')
		{
			decimal += (int)pow(2, i);
		}
	}
	return (decimal);
}

void	signal_handler(int sig)
{
	static char	*text = NULL;
	static char	buffer[8];
	static int	buffer_index = 0;
	static int	count = 0;
	int			decimal_value;
	char		*new_text;

	static int text_len = 0; // Length of the text.
	// Allocate initial space for text if it's NULL
	if (text == NULL) // IN first signal
	{
		text = malloc(1);
		text[0] = '\0';
	}
	if (sig == SIGUSR1)
	{
		buffer[buffer_index++] = '1';
	}
	else if (sig == SIGUSR2)
	{
		buffer[buffer_index++] = '0';
	}
	count++;
	if (count == 7)
	{
		buffer[7] = '\0'; // Null-terminate the buffer.
		decimal_value = binary_to_decimal(buffer);
		if (decimal_value == 0)
		{
			// Message is finished
			printf("Received message: %s\n", text);
			free(text);
			text = NULL;
			text_len = 0;
		}
		else
		{
			// Manually reallocating memory for text.
			new_text = (char *)malloc(text_len + 2);
			//+1 for new char and +1 for null terminator.
			if (new_text == NULL)
			{
				perror("Memory allocation failed");
				free(text); // Free old text to avoid memory leak.
				exit(EXIT_FAILURE);
			}
			// Copy existing text to new_text.
			strcpy(new_text, text);
			// TODO: Discuss how to make it faster.
			new_text[text_len] = (char)decimal_value;
			// Append the new character.
			new_text[text_len + 1] = '\0';
			// Null-terminate the new string.
			free(text); // Free old memory.
			text = new_text;
			text_len++; // Increase the length count.
		}
		buffer_index = 0;
		count = 0;
	}
}

int	main(void)
{
	int					myPid;
	struct sigaction	action;

	myPid = getpid();
	printf("My PID is: %d\n", myPid);
	action.sa_handler = signal_handler;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}

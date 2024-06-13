SRCS    = client.c server.c

OBJS    = $(SRCS:.c=.o)

CC      = gcc
RM      = rm -f

CFLAGS  = -Wall -Wextra -Werror -Ilibft

LIBFT   = libft/libft.a

all:    server client

%.o:    %.c
		$(CC) $(CFLAGS) -c $< -o $@

server: server.o $(LIBFT)
		$(CC) $(CFLAGS) server.o -Llibft -lft -o $@

client: client.o $(LIBFT)
		$(CC) $(CFLAGS) client.o -Llibft -lft -o $@

$(LIBFT):
		$(MAKE) -C libft

clean:
		$(MAKE) clean -C libft
		$(RM) $(OBJS)

fclean: clean
		$(MAKE) fclean -C libft
		$(RM) server client

re:     fclean all

.PHONY: all clean fclean re libft

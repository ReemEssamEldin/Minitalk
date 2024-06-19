# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reldahli <reldahli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 16:31:32 by reldahli          #+#    #+#              #
#    Updated: 2024/06/19 16:54:34 by reldahli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variabls
SERVER = server
CLIENT = client
CC	=	cc
RM	=	rm -rf
CFLAGS	=	-Wall -Wextra -Werror

# Builds both
all: 		$(SERVER)	$(CLIENT)

# Rule to build the SERVER executable from server.c
$(SERVER):	server.c
		@$(CC) $(FLAGS) $<  -o $@
# Rule to build the CLIENT executable from client.c
$(CLIENT):	client.c
		@$(CC) $(FLAGS) $<  -o $@

# Remove the server and client executables
clean:
		@$(RM) $(SERVER) $(CLIENT)
fclean: clean
		$(RM)

re:		fclean all

.PHONY:		all clen fclean re libft
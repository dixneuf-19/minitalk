# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzary <mzary@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 14:45:06 by mzary             #+#    #+#              #
#    Updated: 2024/12/18 14:15:39 by mzary            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server client

all: $(NAME)

server: server.c minitalk.h libft.a
	cc -Wall -Wextra -Werror server.c libft.a -o server

client: client.c minitalk.h libft.a
	cc -Wall -Wextra -Werror client.c libft.a -o client

libft.a:
	make -C libft

bonus: server_bonus client_bonus

server_bonus: server_bonus.c minitalk_bonus.h libft.a
	cc -Wall -Wextra -Werror server_bonus.c libft.a -o server_bonus

client_bonus: client_bonus.c minitalk_bonus.h libft.a
	cc -Wall -Wextra -Werror client_bonus.c libft.a -o client_bonus

clean:
	rm -f libft.a
	make clean -C libft

fclean: clean
	rm -f server client server_bonus client_bonus

re: fclean all

PHONY: clean
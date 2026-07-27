# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/06 12:31:35 by smeza-ro          #+#    #+#              #
#    Updated: 2026/07/27 20:56:22 by smeza-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= codexion

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -lpthread

SRCS		= initializer.c main.c parser.c priority_queue.c \
				utils.c threads.c routine.c acquire_dongle.c
OBJS		= $(SRCS:.c=.o)

HEADER		= codexion.h
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
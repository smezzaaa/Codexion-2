# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smeza-ro <smeza-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/06 12:31:35 by smeza-ro          #+#    #+#              #
#    Updated: 2026/10/01 10:13:36 by smeza-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= codexion

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -lpthread

SRCS		= initializer.c main.c parser.c priority_queue.c \
				utils.c threads.c routine.c acquire_dongle.c monitor.c \
				edge_case_routine.c actions.c
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
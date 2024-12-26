# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 19:24:45 by wdaoudi-          #+#    #+#              #
#    Updated: 2024/12/26 12:37:18 by wdaoudi-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

SRCS = $(addprefix src/, main.c parsing.c utils.c init.c routine.c write.c \
 special.c )

INCLUDES = ./includes

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pthread -g3
SANITIZE = -pthread -g


NAME = philo

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tsan: CFLAGS += $(SANITIZE)
tsan: re

.PHONY: all clean fclean re
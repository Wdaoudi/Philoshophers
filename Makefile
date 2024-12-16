# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/16 19:24:45 by wdaoudi-          #+#    #+#              #
#    Updated: 2024/12/16 19:25:57 by wdaoudi-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

SRCS = $(addprefix src/,  )

INCLUDES = ./includes

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g3 

NAME = philo

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c  $< -o $@ 

$(LIBFT):
	make -C ./libft

$(NAME):  $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES)  $(OBJS) -o $(NAME) 

clean:
	rm -f $(OBJS)
	make clean -C 

fclean: clean
	rm -f $(NAME)
	make fclean -C

re: fclean all

.PHONY: all clean fclean re
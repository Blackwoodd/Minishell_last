# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsalhi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:03:13 by nsalhi            #+#    #+#              #
#    Updated: 2022/11/22 16:57:38 by nsalhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a
CC =	cc
AR =	ar rcs
SRC =	ft_base.c \
	ft_hexa_octa.c \
	ft_number.c \
	ft_pointer.c \
	ft_printf.c \
	ft_strlen.c \
	ft_word.c \

CFGLAGS = -Werror -Wextra -Wall

OBJ = $(SRC:.c=.o)

$(NAME):	$(OBJ)
		$(AR) $(NAME) $(OBJ)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean :	clean
			rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

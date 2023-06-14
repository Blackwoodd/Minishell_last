# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nassm <nassm@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 15:42:51 by nsalhi            #+#    #+#              #
#    Updated: 2023/06/07 17:07:56 by nassm            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	libft.a
CC = 	gcc
AR =	ar rcs
SRC = 	ft_isalpha.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strrchr.c \
	ft_atoi.c \
	ft_isascii.c \
	ft_memchr.c \
	ft_memset.c \
	ft_strlen.c \
	ft_tolower.c \
	ft_bzero.c \
	ft_isdigit.c \
	ft_isspace.c \
	ft_memcmp.c \
	ft_strchr.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_toupper.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_memcpy.c \
	ft_strlcat.c \
	ft_strnstr.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_split_set.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_printf/ft_base.c \
	ft_printf/ft_hexa_octa.c \
	ft_printf/ft_number.c \
	ft_printf/ft_pointer.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_strlen.c \
	ft_printf/ft_word.c \
	get_next_line_utils.c \
	get_next_line.c \
	ft_free_split.c \
	ft_free_str.c \
	ft_setinstr.c \
	ft_putstr.c \
	ft_strclen.c \
	ft_realloc_str.c \
	ft_add_str_to_tab.c \
	ft_str_arr_dup.c \
	ft_append.c \
	ft_strstr.c \
	ft_strstrjoin.c \
	ft_free_single_str.c \
	ft_free_str_array.c \
	ft_str_arr_len.c \
	ft_realloc_str_arr.c \
	ft_free.c \
	ft_append_len_div.c \
	ft_sort_str_arr.c  \
	ft_str_arr_realloc.c \
	ft_perror.c \
	ft_fprintf.c \
	ft_putlhex_fd.c \
	ft_putuhex_fd.c \
	ft_putptr_fd.c \
	ft_putunbr.c \
	ft_putlnbr_fd.c \
	ft_htoa.c \
	ft_putlnbr.c \
	ft_issign.c \
	ft_atol.c \

BONUSSRC =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

ifeq (bonus, $(findstring bonus, $(MAKECMDGOALS)))
	SRC = $(BONUSSRC)
endif

CFLAGS += -Werror -Wextra -Wall -g3

OBJ = $(SRC:.c=.o)

BONUSOBJ = $(BONUSSRC:.c=.o)

$(NAME): $(OBJ)
	 $(AR) $(NAME) $(OBJ)

all:	$(NAME)

bonus: $(NAME)

clean:
	rm -rf $(OBJ) $(BONUSOBJ)

fclean: clean
	rm -f $(NAME) $(BONUSOBJ)

re: 	fclean all

.PHONY:		all clean fclean re bonus

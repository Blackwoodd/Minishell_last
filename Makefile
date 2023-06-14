############## NAME #############

NAME		= minishell


############ SOURCES ###########

PATH_SRCS	= srcs/
VPATH		= $(PATH_SRCS)
SRCS 		= $(wildcard $(PATH_SRCS)*.c)
LIBFT_PATH = ./include/libft/
LIBFT = $(LIBFT_PATH)libft.a

########## VARIABLES ############

PATH_OBJS	= objs/
OBJS		= $(patsubst $(PATH_SRCS)/%.c, $(PATH_OBJS)/%.o, $(SRCS))
RM			= @rm -f
CC			= @gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -lreadline

############ REGLES #############

all		:	$(NAME)


$(NAME)	:	$(OBJS)
			@echo "\033[0;31;5m __   __  ___   __    _  ___   _______  __   __  _______  ___      ___     \033[0m"
			@echo "\033[0;31;5m|  |_|  ||   | |  |  | ||   | |       ||  | |  ||       ||   |    |   |    \033[0m"
			@echo "\033[0;31;5m|       ||   | |   |_| ||   | |  _____||  |_|  ||    ___||   |    |   |    \033[0m"
			@echo "\033[0;31;5m|       ||   | |       ||   | | |_____ |       ||   |___ |   |    |   |    \033[0m"
			@echo "\033[0;31;5m|       ||   | |  _    ||   | |_____  ||       ||    ___||   |___ |   |___ \033[0m"
			@echo "\033[0;31;5m| ||_|| ||   | | | |   ||   |  _____| ||   _   ||   |___ |       ||       |\033[0m"
			@echo "\033[0;31;5m|_|   |_||___| |_|  |__||___| |_______||__| |__||_______||_______||_______|\033[0m"
			@echo "\033[0;33mCompilation...\033[0m"
			make -C $(LIBFT_PATH)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
			@echo "\033[0;32mCompilation : OK.\033[0m"

# $(OBJS)	: 	$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c include/philo.h
# 			@mkdir -p $(PATH_OBJS)
# 			@$(CC) $(CFLAGS) -c $< -o $@

clean	:
			@echo "\033[0;33mClean...\033[0m"
			@$(RM) -rf $(PATH_OBJS)
			make clean -C $(LIBFT_PATH)
			@echo "\033[0;32mClean : OK.\033[0m"

fclean	:	clean
			$(RM) $(NAME)
			make fclean -C $(LIBFT_PATH)

re		:		fclean all

.PHONY	:		all clean fclean re
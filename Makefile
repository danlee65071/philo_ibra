NAME = philo

SRC = philo.c ft_philosophers_threads.c ft_atoi.c ft_waiter.c
DIR_SRC = srcs
SRC_PATH = $(addprefix $(DIR_SRC)/, $(SRC))

OBJ	= $(patsubst %.c, %.o, $(SRC))
DIR_OBJ = objects
OBJ_PATH = $(addprefix $(DIR_OBJ)/, $(OBJ))

CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -g

HEADER = philo.h
DIR_HEADER = includes
HEADER_PATH = includes/philo.h

all: $(NAME)

$(NAME): $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(DIR_HEADER) $(OBJ_PATH) -o $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADER_PATH)
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -I $(DIR_HEADER) -c $< -o $@


clean:
				$(RM) $(DIR_OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY: all clean fclean re

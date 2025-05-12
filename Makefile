NAME = philo

MAKEFLAGS = --no-print-directory

INC_DIR = ./inc
INC = -I$(INC_DIR)

SRC_DIR = src
OBJ_DIR = obj

SRC = $(SRC_DIR)/clean.c \
	  $(SRC_DIR)/utils.c \
	  $(SRC_DIR)/init_data.c \
	  $(SRC_DIR)/thread_action.c \
	  $(SRC_DIR)/start_process.c \
	  $(SRC_DIR)/thread_utils.c \
	  main.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-g -gdwarf-4
RM = @rm -rf
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# Variables
NAME        = test
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -I includes -I libft/includes
LIBFT       = libft/libft.a
SRC_DIR     = src
OBJ_DIR     = obj
SRCS        = $(SRC_DIR)/check_input.c\
			$(SRC_DIR)/main.c \
            $(SRC_DIR)/push.c \
            $(SRC_DIR)/radix_sort.c \
            $(SRC_DIR)/reverse_rotate.c \
            $(SRC_DIR)/rotate.c \
            $(SRC_DIR)/small_sort.c \
			$(SRC_DIR)/sort_utils.c \
            $(SRC_DIR)/stack_building.c \
			$(SRC_DIR)/stack_utils.c \
            $(SRC_DIR)/swap.c

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

$(LIBFT):
	@make -C libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re

# Project Name
NAME        = fractol

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

# MinilibX Configuration
MINILIBX_DIR = inc/minilibx-linux
MINILIBX    = -L$(MINILIBX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
MLX_INCLUDE = -L$(MINILIBX_DIR)

# Include Paths
INCLUDES    = -Iinc -Iinc/libft -I$(MINILIBX_DIR)

# Library Paths
LIBFT       = inc/libft/libft.a

# Source and Object Directories
SRC_DIR     = src
OBJ_DIR     = obj

# Source Files
SRCS        = $(SRC_DIR)/main.c \
              $(SRC_DIR)/render.c \
              $(SRC_DIR)/math_utils.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/events.c

# Object Files
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default Target
all: $(NAME)

# Rule to build the final executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MINILIBX) -o $(NAME)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDE) -c $< -o $@

# Rule to create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to build the libft library
$(LIBFT):
	@make -C inc/libft

# Clean up object files
clean:
	rm -rf $(OBJ_DIR)
	@make -C inc/libft clean

# Clean up everything (objects and executable)
fclean: clean
	rm -f $(NAME)
	@make -C inc/libft fclean

# Rebuild the project
re: fclean all

# Phony targets to avoid conflicts with files of the same name
.PHONY: all clean fclean re
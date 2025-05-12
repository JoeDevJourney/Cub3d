
# Library Name
NAME        = cub3D

# Libraries
LIBFT_DIR   = include/libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = MLX42
MLX_FLAGS   = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Colors for terminal output
GREEN  = \033[0;32m
BLUE   = \033[0;34m
ORANGE = \033[38;5;214m
RED    = \033[0;31m
YELLOW = \033[0;33m
RESET  = \033[0m

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

# Include flags
INC         = -I$(INC_DIR) -I$(LIBFT_DIR)/inc -I$(MLX_DIR)/include

# Source files
SRC_FILES   = main.c \
              parser/parser.c \
              parser/validation.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ────────────────────────────────────────────────────────────────────────────────
# Default target
all: $(NAME)

# Link executable
$(NAME): $(LIBFT) $(MLX_DIR)/build/libmlx42.a $(OBJS)
	@echo "$(ORANGE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)** $(NAME) Compiled successfully! **$(RESET)"

# Build libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Build MLX42
$(MLX_DIR)/build/libmlx42.a:
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build

# Compile .c → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $< ...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ────────────────────────────────────────────────────────────────────────────────
# Cleanup
clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR)/build clean
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)** Cleaned object files **$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)** Removed $(NAME) **$(RESET)"

re: fclean all

# ────────────────────────────────────────────────────────────────────────────────
.PHONY: all clean fclean re

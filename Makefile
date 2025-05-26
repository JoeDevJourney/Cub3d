
# Library Name
NAME        = cub3D

# Libraries
LIBFT_DIR   = include/libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = MLX42
MLX_LIB     = $(MLX_DIR)/build/libmlx42.a
MLX_REPO    = https://github.com/codam-coding-college/MLX42.git
MLX_FLAGS   = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
# MLX_FLAGS = $(MLX_LIB) \
#             $(MLX_DIR)/build/_deps/glfw-build/src/libglfw3.a \
#             -lX11 -lXrandr -lXi -lXxf86vm -lXcursor -lGL -lm -ldl -pthread

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
              parser/validation.c \
			  parser/normalization.c \
			  parser/player.c \
			  parser/color.c \
			  parser/texture.c \
			  parser/utils.c \
			  parser/utils2.c \
			  parser/utils3.c \
			  parser/closure.c \
			  event.c \
			  moving.c \
			  raycast.c \
			  render_column.c \
			  render_frame.c \
			  utils.c \




SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ────────────────────────────────────────────────────────────────────────────────
# Default target
all: $(NAME)

# Link executable
$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@echo "$(ORANGE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)** $(NAME) Compiled successfully! **$(RESET)"

# Build libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# ─ Download & build MLX42 in one target ───────────────────────────────────────
$(MLX_LIB):
	@# Clone if needed
	@if [ ! -d $(MLX_DIR) ]; then \
	  echo "$(BLUE)** Downloading MLX42... **$(RESET)"; \
	  git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@# Build
	@echo "$(ORANGE)** Building MLX42... **$(RESET)"
	@cd $(MLX_DIR) && cmake -B build && cmake --build build

# Compile .c → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $< ...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ────────────────────────────────────────────────────────────────────────────────
# Cleanup
clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)** Cleaned object files **$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@rm -rf $(MLX_DIR)
	@echo "$(RED)** Removed $(NAME) and MLX42 directory **$(RESET)"

re: fclean all

# ────────────────────────────────────────────────────────────────────────────────
.PHONY: all clean fclean re

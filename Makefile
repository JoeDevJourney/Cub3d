

# ─────────── Variables ───────────────────────────────────────────────────────
NAME       = cub3D
SRCDIR     = src
PARSERDIR  = $(SRCDIR)/parser
OBJDIR     = obj
INCDIR     = include
LIBFTDIR   = $(INCDIR)/libft
LIBMLX     = MLX42
LIB        = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Source files (full paths)
SRCS       = $(SRCDIR)/main.c \
             $(PARSERDIR)/parser.c

# Object files: strip directories, then prefix with obj/
OBJS       = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

LIBFT      = $(LIBFTDIR)/libft.a

# Include flags
CFLAGS    := -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFTDIR)/inc

# ─────────── Default target ──────────────────────────────────────────────────
all: gitclone libmlx $(LIBFT) $(NAME)

# ─────────── MLX & libft targets ────────────────────────────────────────────
gitclone:
	@if [ ! -d "$(LIBMLX)" ]; then \
	  echo "Cloning MLX42..."; \
	  git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

libmlx: $(LIB)

$(LIB):
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# ─────────── Build executable ───────────────────────────────────────────────
$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
	@echo "\033[33mCompiling $(NAME)...\033[0m"
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFTDIR) -lft $(LIB)
	@echo "\033[32m$(NAME) built successfully!\033[0m"

# ─────────── Object directory ────────────────────────────────────────────────
$(OBJDIR):
	mkdir -p $(OBJDIR)

# ─────────── Explicit rules for each .o ─────────────────────────────────────
# obj/main.o ← src/main.c
$(OBJDIR)/main.o: $(SRCDIR)/main.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# obj/parser.o ← src/parser/parser.c
$(OBJDIR)/parser.o: $(PARSERDIR)/parser.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ─────────── Cleanup ────────────────────────────────────────────────────────
clean:
	@echo "\033[33mCleaning build files…\033[0m"
	rm -rf $(OBJDIR)
	rm -rf $(LIBMLX)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@echo "\033[33mRemoving binaries…\033[0m"
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

# ─────────── Phony targets ──────────────────────────────────────────────────
.PHONY: all clean fclean re gitclone libmlx

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I$(INCDIR) -I$(LIBFTDIR)/include  #-fsanitize=address
MAKEFLAGS += -s

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
LIBFTDIR = ./include/libft
LIBMLX = ./MLX42
LIB = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS = 
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
LIBFT = $(LIBFTDIR)/libft.a
NAME = cub3D

all: gitclone libmlx libft $(NAME)

gitclone:	
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

libmlx: $(LIBMLX)/build/libmlx42.a

$(LIBMLX)/build/libmlx42.a: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
	@echo "\033[33mCompilating $(NAME)...\033[0m"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft
	@echo "$(NAME) compiled \033[32msuccessfully\033[0m!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(GNLDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/builtins/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/utils/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	@echo "\033[33mRemoving project build and library build...\033[0m"
	rm -f $(OBJDIR)/*.o
	rm -rf $(OBJDIR)
	rm -rf $(LIBMLX)
	$(MAKE) -C $(LIBFTDIR) clean
	@echo "All build files removed \033[32msuccessfully\033[0m!"

fclean: clean
	@echo "\033[33mRemoving executable and static libraries...\033[0m"
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	@echo "Executable and static libraries removed \033[32msuccessfully\033[0m!"
	
re: fclean all

.PHONY: all clean fclean re

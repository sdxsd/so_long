# Basic data
CC = clang
CFLAGS = -g -Wall -Wextra -Werror
NAME = so_long
LIB = libft/libft.a
MLX = MLX42/libmlx42.a
CFILES = \
			src/rndr_matrix.c \
			src/parse.c \
			src/game.c \
			src/textures.c \
			src/dealloc.c \
			src/haring.c \
			src/main.c
B_FILES = \
			src/enemy_bonus.c \
			src/femmax_bonus.c \
			src/step_bonus.c \
			src/dealloc_bonus.c
BFLAGS = -D BONUS=1
OFILES = $(CFILES:.c=.o)
OSFLAG = ""
LINKEN = ""
CWB = 0

ifdef MAKE_BONUS
	CFLAGS += $(BFLAGS)
	CFILES += $(B_FILES)
	OFILES = $(CFILES:%.c=%.o)
endif

B_OFILES = $(B_FILES:.c=.o)

# Checks for OS and compiles accordingly.
ifeq ($(shell uname -s),Linux)
	OSFLAG := linux
	CFLAGS += -D LINUX=1
	LINKEN := -I ./MLX42/include/MLX42/ -ldl -lGL -lglfw -lX11 -lpthread -lXrandr -lXi \
	MLX42/libmlx42.a libft/libft.a
else
	OSFLAG := darwin
	CFLAGS += -D DARWIN=1
	LINKEN := -lglfw -L /Users/wmaguire/.brew/opt/glfw/lib/ -lmlx42 -L ./MLX42/ \
	MLX42/libmlx42.a libft/libft.a
endif

all: $(NAME)

$(NAME): $(OFILES) $(LIB) $(MLX)
	@echo "Building for: $(OSFLAG)"
	$(CC) $(CFLAGS) $(OFILES) $(LINKEN) -o $(NAME)

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@
	@echo "COMPILED:" $<

$(MLX):
	@make -C MLX42/

$(LIB):
	@make -C libft/

re: fclean all

bonus:
	make MAKE_BONUS=1

clean:
	rm -f so_long

fclean: clean
	@rm -rfv so_long.dSYM
	@rm -rfv $(OFILES)
	@rm -rfv $(B_OFILES)
	@make -C libft/ fclean
	@make -C MLX42/ fclean

.PHONY: all clean fclean re bonus

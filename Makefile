# Basic data
CC = clang
CFLAGS = -g -Wall -Wextra -Werror
NAME = so_long
CFILES = \
			src/main.c \
			src/parse.c \
			src/rndr_matrix.c \
			src/game.c \
			src/textures.c \
			src/dealloc.c \
			src/haring.c
B_FILES = \
			src/enemy_bonus.c \
			src/femmax_bonus.c \
			src/death_bonus.c
BFLAGS = -D BONUS=1
OFILES = $(CFILES:.c=.o)
OSFLAG = ""
LINKEN = ""

# Checks for OS and compiles accordingly.
ifeq ($(shell uname -s),Linux)
	OSFLAG := linux
	LINKEN := -D LINUX=1 -I ./MLX42/include/MLX42/ -ldl -lGL -lglfw -lX11 -lpthread -lXrandr -lXi
else
	OSFLAG := darwin
	LINKEN := -D DARWIN=1 -lglfw -L /Users/wmaguire/.brew/opt/glfw/lib/ -lmlx42 -L ./MLX42/
endif

all: $(NAME)

$(NAME): lib MLX
	@echo "Building for: $(OSFLAG)"
	$(CC) $(CFLAGS) $(CFILES) $(LINKEN) libft/libft.a MLX42/libmlx42.a -g -o $(NAME)

bonus: lib MLX
	@echo "Building for: $(OSFLAG)"
	$(CC) $(CFLAGS) $(BFLAGS) $(CFILES) $(B_FILES) $(LINKEN) libft/libft.a MLX42/libmlx42.a -o $(NAME)

test: re_test
	./so_long maps/map02.ber

MLX:
	@make -C MLX42/

lib:
	@make -C libft/

valtest: re_test libft
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./so_long maps/map02.ber

re_test: clean bonus

re: fclean all

clean:
	rm -f so_long

fclean: clean
	rm -f *vgcore*
	rm -rfv so_long.dSYM
	make -C libft/ clean
	make -C MLX42/ fclean

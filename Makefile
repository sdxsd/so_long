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
			src/haring.c \
			src/movement.c
OFILES = $(CFILES:.c=.o)
OSFLAG = ""
LINKEN = ""

# Checks for OS and compiles accordingly.
ifeq ($(shell uname -s),Linux)
	OSFLAG := linux
	LINKEN := -I ./MLX42/include/MLX42/ -ldl -lGL -lglfw -lX11 -lpthread -lXrandr -lXi
else
	OSFLAG := darwin
	LINKEN := -lglfw -L /Users/wmaguire/.brew/opt/glfw/lib/ -lmlx42 -L ./MLX42/
endif

all: $(NAME)

$(NAME):
	@echo "Building for: $(OSFLAG)"
	@make -C libft/
	@make -C MLX42/
	$(CC) $(CFLAGS) $(CFILES) $(LINKEN) libft/libft.a MLX42/libmlx42.a -g -o $(NAME)

test: re
	./so_long maps/map02.ber

valtest: re
	valgrind --tool=memcheck --leak-check=full ./so_long maps/map02.ber

re: fclean all

clean:
	rm -f so_long

fclean: clean
	rm -f *vgcore*
	rm -rfv so_long.dSYM
	make -C libft/ clean
	make -C MLX42/ fclean

CC = clang
CFLAGS = -fsanitize=address -Wall -Wextra -Werror
NAME = so_long
CFILES = \
			src/main.c \
			src/parse.c \
			src/rndr_matrix.c \
			src/game.c
OFILES = $(CFILES:.c=.o)
OSFLAG = ""
LINKEN = ""

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
	$(CC) -Wall -Wextra -Werror $(CFILES) $(LINKEN) libft/libft.a MLX42/libmlx42.a -g -o $(NAME)

test: re
	./so_long maps/map02.ber

valtest: re
	valgrind --tool=memcheck ./so_long maps/map01.ber

re: clean all

clean:
	rm -f so_long
	rm -f *vgcore*
	rm -rfv so_long.dSYM
	make -C libft/ clean

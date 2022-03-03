CC = clang
CFLAGS = -g -Wall -Wextra -Werror
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
	LINKEN := -lmlx42 -ldl -lGL -lglfw -lX11 -lpthread -lXrandr -lXi
else
	OSFLAG := darwin
	LINKEN := -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_$(OSFLAG) -O3 -c $< -o $@

$(NAME): $(OBJ)
	@echo "Building for: $(OSFLAG)"
	make -C libft/
	$(CC) -Wall -Wextra -Werror $(CFILES) $(LINKEN) libft/libft.a -g -o $(NAME)

test: re
	./so_long maps/map02.ber

valtest: re
	valgrind --tool=memcheck ./so_long maps/map01.ber

re: clean all

clean:
	rm -f so_long
	rm -f *vgcore*
	rm -f so_long.dSYM
	make -C libft/ clean

CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
CFILES = \
			src/main.c
OFILES = $(CFILES:.c=.o)
OSFLAG = ""
LINKEN = ""

ifeq ($(shell uname -s),Linux)
	OSFLAG := linux
	LINKEN := -lmlx -lXext -lX11
else
	OSFLAG := darwin
	LINKEN := -lmlx_Darwin -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm -framework OpenGL -framework AppKit
endif

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_$(OSFLAG) -O3 -c $< -o $@


$(NAME): $(OBJ)
	@echo "Building for: $(OSFLAG)"
	$(CC) $(OBJ) $(CFILES) -Lmlx_$(OSFLAG) $(LINKEN) -o $(NAME)

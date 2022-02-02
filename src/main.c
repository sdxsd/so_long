/*
SO_LONG (Implementation of Codam project so_long)
Copyright (C) 2021  Will Maguire

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>

The definition of Free Software is as follows:
		- The freedom to run the program, for any purpose.
		- The freedom to study how the program works, and adapt it to your needs.
		- The freedom to redistribute copies so you can help your neighbor.
		- The freedom to improve the program, and release
		your improvements to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include <mlx.h>
#include "../include/so_long.h"
#include "../include/parse.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

static void belgie(void *mlx, int blksiz)
{
	t_data	img;
	void	*win;
	win = mlx_new_window(mlx, 128, 128, "so_long");
	img.img = mlx_xpm_file_to_image(mlx, "./images/wall.xpm", &blksiz, &blksiz);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_the_matrix	*sim_env;
	void			*mlx;
	int	blksiz = 128;

	mlx = mlx_init();
	sim_env = matrix_init(argc, argv);
	if (!sim_env)
	{
		ft_putstr("Invalid map...\n");
		return (1);
	}
	ft_printf("X: %d\nY: %d\n", sim_env -> x, sim_env -> y);
	ft_printf("BLKNUM: %d\n", sim_env -> x * sim_env -> y);
	belgie(mlx, blksiz);
	mlx_loop(mlx);
}

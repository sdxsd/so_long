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

#include "../include/rndr_matrix.h"

int	rndr_matrix(t_the_matrix *matrix)
{
	void	*mlx;
	void	*win;
	int		img_x;
	int		img_y;
	//int		iterator;
	//int		iterator_2;
	t_data	render_data;

	//iterator = 0;
	//iterator_2 = 0;
	img_x = BLKSIZ;
	img_y = BLKSIZ;
	mlx = mlx_init();
	render_data.img = mlx_xpm_file_to_image(mlx, "./images/wall.xpm", &img_x, &img_y);
	win = mlx_new_window(mlx, matrix -> x * BLKSIZ, matrix -> y * BLKSIZ, "so_long");
	matrix -> simulation_data -= matrix -> y;
	ft_printf("%s\n", *matrix -> simulation_data - 2);
	mlx_put_image_to_window(mlx, win, render_data.img, 0, 0);
	//while (matrix -> simulation_data != NULL && iterator_2 < matrix -> y)
	//{
	//	while (iterator < matrix -> x)
	//	{
	//		if (*matrix -> simulation_data[iterator] == '#')
	//			mlx_put_image_to_window(mlx, win, render_data.img, 0, 0);
	//iterator++;
	//	}
	//	iterator_2++;
	//	matrix -> simulation_data++;
	//}
	mlx_loop(mlx);
	return (0);
}

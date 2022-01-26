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
#include <unistd.h>
#include <stdio.h>

int nederland(void *win,int w,int h, void *mlx)
{
	int   x;
	int   y;
	int   color;

	color = 0x0003DA5;
	y = h;
	while (y--)
	{
		x = w;
		while (x--)
		{
			if (y == 200)
				color = 0x00C8102E;
			if (y == 400)
				color = 0xFFFFFFFF;
			mlx_pixel_put(mlx, win, x, y, color);
		}
	}
	return (0);
}


int	main(void)
{
	void	*mlx_win;
	void	*img;
	void	*mlx;


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "Nederland");
	img = mlx_new_image(mlx, 800, 600);

	nederland(mlx_win, 800, 600, mlx);
	mlx_loop(mlx);
}

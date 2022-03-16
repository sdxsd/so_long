/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CODAM C FILE                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire     ########   codam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

#include "../include/death_bonus.h"
#include "../include/dealloc.h"
#include "../include/rndr_matrix.h"

static mlx_image_t	*rndr_black(mlx_t *mlx, t_matrix *matrix)
{
	mlx_image_t	*bckgrnd;
	int			px;
	int			py;
	int			colour;

	px = 0;
	py = 0;
	colour = 0x00000000;
	bckgrnd = mlx_new_image(mlx, matrix->x * BLKSIZ, matrix->y * BLKSIZ);
	while (py < matrix->x * BLKSIZ)
	{
		while (px < matrix->y * BLKSIZ)
		{
			mlx_put_pixel(bckgrnd, px, py, colour);
			px++;
		}
		px = 0;
		py++;
	}
	return (bckgrnd);
}

void	you_died(t_reality	*reality)
{
	mlx_image_t	*background;
	int			string_x;
	int			string_y;

	string_x = (reality->matrix->x / 2);
	string_y = (reality->matrix->y / 2);
	background = rndr_black(reality->mlx, reality->matrix);
	mlx_image_to_window(reality->mlx, background, 0, 0);
	mlx_put_string(reality->mlx, "YOU DIED", string_x, string_y);
}

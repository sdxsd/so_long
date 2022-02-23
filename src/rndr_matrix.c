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

#include "../include/rndr_matrix.h"

static t_texdata	*load_textures(void)
{
	t_texdata	*tex_struct;

	tex_struct = malloc(sizeof(tex_struct));
	if (!tex_struct)
		return (NULL);
	tex_struct -> wall = mlx_load_png("./images/wall.png");
	tex_struct -> coll = mlx_load_png("./images/coll.png");
	tex_struct -> exit = mlx_load_png("./images/exit.png");
	tex_struct -> plyr = mlx_load_png("./images/plyr.png");
	if (!tex_struct -> wall || !tex_struct -> coll)
		return (NULL);
	if (!tex_struct -> exit || !tex_struct -> plyr)
		return (NULL);
	return (tex_struct);
}

static t_mlx_image	*map_blk(void *mlx, char blk)
{
	static t_texdata	*tex_struct;

	if (!tex_struct)
		tex_struct = load_textures();
	if (blk == 'C')
		return (mlx_texture_to_image(mlx, tex_struct -> coll));
	if (blk == 'P')
		return (mlx_texture_to_image(mlx, tex_struct -> plyr));
	if (blk == '1')
		return (mlx_texture_to_image(mlx, tex_struct -> wall));
	if (blk == 'E')
		return (mlx_texture_to_image(mlx, tex_struct -> exit));
	else
		return (NULL);
}

static int	rndr_line(void *mlx, char *mline, int lsize, int y)
{
	int			iterator;
	int			pos_x;
	int			pos_y;
	t_mlx_image	*img;

	iterator = 0;
	pos_x = 0;
	pos_y = y * 32;
	while (iterator < lsize)
	{
		img = map_blk(mlx, mline[iterator]);
		mlx_image_to_window(mlx, img, pos_x, pos_y);
		pos_x += 32;
		iterator++;
	}
	return (TRUE);
}

int	rndr_matrix(t_the_matrix *matrix)
{
	void		*mlx;
	char		*line;

	line = "1CEP1PEC1CEE1EEP";
	mlx = mlx_init(matrix -> x * BLKSIZ, matrix -> y * BLKSIZ, "so_long", TRUE);
	rndr_line(mlx, line, 16, 0);
	rndr_line(mlx, line, 16, 1);
	rndr_line(mlx, line, 16, 2);
	rndr_line(mlx, line, 16, 3);
	rndr_line(mlx, line, 16, 4);
	mlx_loop(mlx);
	return (0);
}

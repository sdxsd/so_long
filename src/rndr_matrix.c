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
#include "../include/dealloc.h"
#include "../include/haring.h"
#ifdef BONUS
# include "../include/enemy_bonus.h"
# include "../include/step_bonus.h"
#endif

/* Takes the width and height of the MLX window and generates a background. */
/* Functions by taking the win_y argument and */
/* defining 3 distinct stages and changing the background colour */
/* value based on said stages. */
/* The win_x value is used as an iterator and fills each line of the */
/* image with the colour defined. */
static mlx_image_t	*rndr_background(mlx_t *mlx, int win_x, int win_y)
{
	mlx_image_t	*bckgrnd;
	int			px;
	int			py;
	int			colour;

	px = 0;
	py = 0;
	colour = 0xFF9B00FF;
	bckgrnd = mlx_new_image(mlx, win_x, win_y);
	while (py < win_y)
	{
		while (px < win_x)
		{
			mlx_put_pixel(bckgrnd, px, py, colour);
			px++;
		}
		if (py > (win_y / 3))
			colour = 0xFFFFFFFF;
		if (py > (win_y / 3 * 2))
			colour = 0x0B72FFFF;
		px = 0;
		py++;
	}
	return (bckgrnd);
}

/* Takes a string of map data as input and outputs the rendered equivalent. */
/* Functions by taking a line to interpret, the */
/* total size of the line, and a y position to render */
/* the aforementioned line at. */
/* Defines two index variables, pos_x, and pos_y. */
/* pos_x is set to the first block in the */
/* row. pos_y is set to the row defined */
/* by the y argument. */
/* The window is defined as a series of blocks. */
/* By block I mean a square of 32x32 pixels. */
/* For example vertical row five, at horizontal position 3 */
/* would be expressed in pixel terms as y 160 and x 96. */
/* 32 * 5 down, and 32 * 3 across. */
/* For each character in the given line, the character */
/* is mapped to the equivalent map texture with map_blk() */
/* and then pushed to the image at the current offset of pos_x */
/* and at the row defined by pos_y. */
/* pos_x is then increased by one block to the right (+32), and */
/* the loop repeats. */
/* Returns TRUE at return. */
static int	rndr_line(t_reality *reality, char *mline, int lsize, int y)
{
	int			iterator;
	int			pos_x;
	int			pos_y;

	iterator = 0;
	pos_x = 0;
	pos_y = y * BLKSIZ;
	while (iterator < lsize)
	{
		if (mline[iterator] == 'C')
			register_haring(reality, iterator, y);
		else
			mlx_image_to_window(reality->mlx, \
								map_blk(reality->textures, mline[iterator]), \
								pos_x, pos_y);
		pos_x += BLKSIZ;
		iterator++;
	}
	return (TRUE);
}

/* Handles the first render of the game, */
// In MLX42 rendering images multiple times will eventually
// cause a stack based buffer overflow, as the amount of memory
// allocated to images becomes too great. To move each image
// rather than render it again, you must change the x and y position of the
// image instance within the struct. This function renders
// the map for the first time, including the sprites that will
// eventually be moved in other functions.
// The textures are also load in this function with load_textures().
// The function then uses rndr_bckgrnd() to prepare the background
// image.
// Continuing, the function iterates through the two dimensional array
// of map data, rendering each line as it goes with the subroutine
// rndr_line()
// It then renders the player, before checking whether the bonus is activated
// and if it is, then the enemies are generated.
// The function shall then return.
static int	first_rndr(t_reality *reality)
{
	int					iter;
	t_matrix			*matrix;

	matrix = reality->matrix;
	reality->textures = load_textures(reality->mlx);
	reality->bckgrnd = \
		rndr_background(reality->mlx, \
						matrix->x * BLKSIZ, matrix->y * BLKSIZ);
	mlx_image_to_window(reality->mlx, reality->bckgrnd, 0, 0);
	matrix->simulation_data = matrix->wired_entry;
	iter = 0;
	while (iter < matrix->y)
	{
		rndr_line(reality, *matrix->simulation_data, matrix->x, iter);
		matrix -> simulation_data++;
		iter++;
	}
	mlx_image_to_window(reality->mlx, reality->textures->plyr, \
						matrix->plyr_x, matrix->plyr_y);
	matrix->simulation_data = matrix->wired_entry;
	if (BONUS)
		gen_enemies(reality->mlx, reality);
	return (TRUE);
}

int	rndr_matrix(t_reality *reality)
{
	static int	rndrd;
	t_matrix	*mtrx;

	mtrx = reality -> matrix;
	if (!rndrd)
		rndrd = first_rndr(reality);
	if (BONUS)
		display_steps(reality->mlx, mtrx->step_c);
	if (reality->textures->plyr->instances)
	{
		reality->textures->plyr->instances[0].x = mtrx->plyr_x;
		reality->textures->plyr->instances[0].y = mtrx->plyr_y;
	}
	return (TRUE);
}

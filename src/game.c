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

// All things repeat in echo of eachother.
// But my keypresses shouldn't be...

#include "../include/game.h"
#include "../include/dealloc.h"

static int	val_move(int x, int y, t_matrix *matrix)
{
	matrix -> simulation_data = matrix -> wired_entry;
	if (matrix -> simulation_data[y / 32][x / 32] == '1')
		return (FALSE);
	return (TRUE);
}

static void handle_key(char key, t_reality *reality)
{
	int	*plyr_x;
	int	*plyr_y;

	plyr_x = &reality -> matrix -> plyr_x;
	plyr_y = &reality -> matrix -> plyr_y;
	if (key == 'W' && val_move(*plyr_x, *plyr_y - BLKSIZ, reality -> matrix))
		*plyr_y -= BLKSIZ;
	if (key == 'A' && val_move(*plyr_x - BLKSIZ, *plyr_y, reality -> matrix))
		*plyr_x -= BLKSIZ;
	if (key == 'S' && val_move(*plyr_x, *plyr_y + BLKSIZ, reality -> matrix))
		*plyr_y += BLKSIZ;
	if (key == 'D' && val_move(*plyr_x + BLKSIZ, *plyr_y, reality -> matrix))
		*plyr_x += BLKSIZ;
	ft_printf("X: %d | Y: %d\n", *plyr_x / 32, *plyr_y / 32);
	return ;
}

static void	keycodes(mlx_key_data_t keydata, void *param)
{
	t_reality	*reality;
	const char	*keydict = "WASD";

	reality = param;
	if (keydata.action == MLX_PRESS)
	{	if (ft_charchk(keydata.key, (char *)keydict))
			handle_key(keydata.key, reality);
		else if (keydata.key == MLX_KEY_ESCAPE)
			free_and_exit(reality);
	}
	if (!rndr_matrix(reality))
		ft_printf("RENDER FAILED\n");
	return ;
}

// Function to handle the gameloop and input.
int	gameloop(t_reality *reality)
{
	mlx_key_hook(reality -> mlx, keycodes, reality);
	mlx_loop(reality -> mlx);
	return (TRUE);
}

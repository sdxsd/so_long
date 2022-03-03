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

// The design of this so_long is intentional.
// The player sprite represents the primacy of The Netherlands.
// The wall sprite represents how the Belgian menace holds us back.
// The collectible sprite represents the goal that all good Dutch people desire.
// The exit represents Mark Rutte as our exit.
// The background is symbolic of the monarchy, the backbone of the nation.
// Je maintiendrai!

#include "../include/so_long.h"
#include "../include/parse.h"
#include "../include/rndr_matrix.h"

static void	*init_reality(t_reality *reality)
{
	t_matrix	*matr;

	matr = reality -> matrix;
	reality -> mlx = mlx_init(matr -> x * BLKSIZ, matr -> y * BLKSIZ, "so_long", TRUE);
	if (!reality -> mlx)
		return (NULL);
	return (reality -> mlx);
}

// This function initiates the program.
// Begins by using the matrix_init() function to interpret
// and load the map.
// Then begins the rendering process with
// rndr_matrix() before entering the game loop.
// Upon exit will call a cleanup function to deallocate residual memory.
int	main(int argc, char *argv[])
{
	t_reality	*reality;

	reality = malloc(sizeof(t_reality));
	reality -> matrix = matrix_init(argc, argv);
	if (!reality -> matrix)
	{
		ft_putstr("ERROR:\nInvalid map...\n");
		return (1);
	}
	ft_putstr("so_long Copyright (C) 2022 Will Maguire\n");
	init_reality(reality);
	rndr_matrix(reality);
	mlx_loop(reality -> mlx);
}

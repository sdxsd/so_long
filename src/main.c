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

/* The design of this so_long is intentional. */
/* The player sprite represents the primacy of The Netherlands. */
/* The wall sprite represents how the Belgian menace holds us back. */
/* The collectible sprite represents the goal that good Dutch people desire. */
/* The exit represents Mark Rutte as our exit. */
/* The background is symbolic of the monarchy, the backbone of the nation. */
/* Je maintiendrai! */

#include "../include/so_long.h"
#include "../include/parse.h"
#include "../include/rndr_matrix.h"
#include "../include/game.h"
#include "../include/haring.h"

/* This function initializes the reality struct */
/* which holds most if not all of the game state data. */
/* Calls mlx_init() to begin window rendering. */
/* Sets reality->textures to null, this is important because */
/* otherwise it will be set to a random address in memory */
/* and the check in rndr_matrix() of if the textures have loaded */
/* will be invalid and segfault the program. */
/* Finally checks if mlx has loaded, returning null if not. */
/* Otherwise returns NULL */
/* Initialises the x and y of the plyr to 0, if */
/* after the map is parsed player still equals 0, then */
/* the map is invalid. */
static void	*init_reality(t_reality *reality)
{
	mlx_t		*mlx;
	t_matrix	*matr;

	matr = reality->matrix;
	matr->step_c = 0;
	matr->plyr_x = 0;
	matr->plyr_y = 0;
	mlx = mlx_init(matr->x * BLKSIZ, matr -> y * BLKSIZ, "NederSim", TRUE);
	reality->textures = NULL;
	reality->bckgrnd = NULL;
	reality->mlx = mlx;
	if (!reality->mlx)
		return (NULL);
	return (reality->mlx);
}

/* This function initiates the program. */
/* Allocates memory for the reality struct */
/* which holds the data of the games state. */
/* initiates the matrix struct, which is a substruct */
/* of the reality struct. It holds the map data and */
/* the player position. matrix_init() */
/* also loads, and validates the map. */
/* If this function fails, reality is also freed. */
/* The haring_db struct is initialised. It holds the data */
/* necessary for collectible functionality. */
/* Puts some basic output text. */
/* Before initialising the reality struct fully. */
/* Which also initialises MLX */
/* Upon exit will call a cleanup function to deallocate residual memory. */
int	main(int argc, char *argv[])
{
	t_reality	*reality;

	reality = malloc(sizeof(t_reality));
	if (!reality)
		return (1);
	reality->matrix = matrix_init(argc, argv);
	if (!reality->matrix)
	{
		ft_putstr("ERROR:\nInvalid map...\n");
		free(reality);
		return (1);
	}
	reality->haring_db = init_haring(reality->matrix->x, reality->matrix->y);
	if (!reality->haring_db)
		return (1);
	ft_putstr("NederSim Copyright (C) 2022 Will Maguire\n");
	ft_putstr("\t⚒ Great design shows, never tells. ⚒\n");
	if (!init_reality(reality))
		return (1);
	rndr_matrix(reality);
	gameloop(reality);
}

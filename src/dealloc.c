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

#include "../include/dealloc.h"

/* Deallocates the texture data. */
/* Goes through each texture loaded and */
/* frees them. Then frees the pointers, and finally the */
/* struct before returning. */
int	free_textures(mlx_t *mlx, t_imgdata *textures)
{
	if (textures -> wall)
		mlx_delete_image(mlx, textures -> wall);
	if (textures -> coll)
		mlx_delete_image(mlx, textures -> coll);
	if (textures -> plyr)
		mlx_delete_image(mlx, textures -> plyr);
	if (textures -> exit)
		mlx_delete_image(mlx, textures -> exit);
	free(textures -> wall);
	free(textures -> coll);
	free(textures -> plyr);
	free(textures -> exit);
	free(textures);
	return (0);
}

/* Deallocates the memory associated with the t_haring struct. */
/* Iterates over the vertical and horizontal rows freeing */
/* as it goes. Then returns a pointer to the freed memory. */
t_haring	*free_haring(t_haring *haring)
{

	free(haring);
	return (haring);
}

/* Deallocates the matrix struct. */
/* Functions by first setting */
/* simulation_data to the first */
/* line of map data (pointed to by wired_entry) */
/* and then iterating over the aforementioned */
/* data freeing it one by one. */
/* Then frees the allocated memory. */
/* Finally frees the struct itself before returning. */
t_matrix	*free_matrix(t_matrix *matrix)
{
	int	iter;

	iter = 0;
	matrix -> simulation_data = matrix -> wired_entry;
	while (iter < matrix -> y)
	{
		free(*matrix -> simulation_data);
		matrix -> simulation_data++;
		iter++;
	}
	free (matrix -> wired_entry);
	free(matrix);
	return (NULL);
}

/* Fully deallocates memory used in the program and exits. */
/* Frees the matrix substruct with free_matrix() */
/* and the textures substruct with free_textures() */
/* Then deallocates the background image. */
/* Finally terminates MLX and frees the struct */
/* for holding all game data before exiting. */
int	free_and_exit(t_reality	*reality)
{
	free_matrix(reality->matrix);
	free_textures(reality->mlx, reality->textures);
	free_haring(reality->haring_db);
	mlx_delete_image(reality->mlx, reality->bckgrnd);
	mlx_terminate(reality->mlx);
	free(reality);
	exit (0);
}

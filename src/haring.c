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
THIS FILE IS PART OF SO_LONG (Implementation of Codam project so_long)
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

#include "../include/haring.h"

// This function initialises the haring struct.
// First the struct itself is allocated,
// and then then the vertical rows of the
// haring_data. If any of these mallocs fail
// the function returns NULL. Then the function
// iterates through each vertical row, and allocates
// the horizontal row. If this fail at any points NULL is returned.
// The haring count is set to 0 to later be set by the register_haring()
// function.
t_haring	*init_haring(int x, int y)
{
	int			iterator_y;
	t_haring	*haring;

	iterator_y = 0;
	haring = malloc(sizeof(t_haring));
	haring->haring_data = malloc(sizeof(int *) * y);
	if (!haring->haring_data)
		return (NULL);
	while (iterator_y < y)
	{
		haring->haring_data[iterator_y] = malloc(sizeof(int) * x);
		if (!haring->haring_data[iterator_y])
			return (NULL);
		iterator_y++;
	}
	haring->haring_c = 0;
	if (!haring->haring_data)
		return (NULL);
	return (haring);
}

// When the program encounters a collectible on the map
// it calls this function, and sets the location of the collectible
// onto the haring matrix while also making a new instance
// on the map of the haring matrix.
int register_haring(t_reality *reality, int x, int y)
{
	t_haring	*haring;

	haring = reality->haring_db;
	haring->haring_c++;
	haring->haring_data[y][x] = \
		mlx_image_to_window(reality->mlx, reality->textures->coll, x * BLKSIZ, y * BLKSIZ);
	return (TRUE);
}

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

t_haring	*init_haring(int x, int y)
{
	int	iterator_y;
	int	iterator_x;
	t_haring	*haring;

	iterator_x = 0;
	iterator_y = 0;
	haring = malloc(sizeof(haring));
	haring->haring_data = malloc(sizeof(mlx_image_t **) * y);
	if (!haring->haring_data)
		return (NULL);
	while (iterator_y < y)
	{
		haring->haring_data[iterator_y] = malloc(sizeof(mlx_image_t *) * x);
		if (!haring->haring_data[iterator_y])
			return (NULL);
		while (iterator_x < x)
		{
			haring->haring_data[iterator_y][iterator_x] = malloc(sizeof(mlx_image_t *));
			if (!haring->haring_data[iterator_y][iterator_x])
				return (NULL);
			iterator_x++;
		}
		iterator_y++;
		iterator_x = 0;
	}
	haring->haring_c = 0;
	if (!haring -> haring_data)
		return (NULL);
	return (haring);
}

int register_haring(t_reality *reality, int x, int y)
{
	t_haring	*haring;

	haring = reality->haring_db;
	haring->haring_data[y][x] = mlx_image_to_window(reality->mlx, reality->textures->coll, 32, 32);
	return (TRUE);
}

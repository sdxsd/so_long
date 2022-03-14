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
THIS FILE IS LICENSED UNDER THE GNU GPLv3
Copyright (C) 2022  Will Maguire

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

/* The name of this file is a #WQ TQWRE$T$#QWER#EZ@EZ@T # */

#include "../include/femmax_bonus.h"
#include "../include/enemy_bonus.h"

static int	ret_move(int dir, int x, int y, t_matrix *matrix)
{
	int	move;
	int	valid_move;

	valid_move = 0;
	while (!valid_move)
	{
		move = get_random(0, 1);
		if (!move)
			move--;
		if (dir)
		{
			if (matrix->simulation_data[y][x + move] != '1')
				valid_move = 1;
			else if (matrix->simulation_data[y][x - move] != '1')
				return (-1 * 32);
			else
				return (0);
		}
		else
		{
			if (matrix->simulation_data[y + move][x] != '1')
				valid_move = 1;
			else if (matrix->simulation_data[y - move][x] != '1')
				return (-1 * 32);
			else
				return (0);
		}
	}
	ft_printf("MOVE: %d\n", move);
	return (move * 32);
}

int	move_femmaxen(t_matrix *mtrx, t_enemy_db *enemies)
{
	int				iter;
	int				dir;
	int				curr_x;
	int				curr_y;
	int				index;

	iter = 0;
	while (iter < enemies->enemy_count)
	{
		index = enemies->e_registry[iter]->i_index;
		curr_x = enemies->enemy_tex->instances[index].x / 32;
		curr_y = enemies->enemy_tex->instances[index].y / 32;
		dir = get_random(0, 1);
		if (dir)
			enemies->enemy_tex->instances[index].x += ret_move(dir, curr_x, curr_y, mtrx);
		else
			enemies->enemy_tex->instances[index].y += ret_move(dir, curr_x, curr_y, mtrx);
		iter++;
	}
	return (TRUE);
}

int	rndr_femmax(mlx_t *mlx, int x, int y, t_enemy_db *enemies)
{
	mlx_image_to_window(mlx, enemies->enemy_tex, x * BLKSIZ, y * BLKSIZ);
	return (TRUE);
}

/* What is femmax? A question etched upon the minds of the */
/* pitiful fool who chooses to read the code curled between the curly braces. */
int	load_femmax(mlx_t *mlx, t_enemy_db *enemies)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png("images/femmax.png");
	if (!tex)
		return (FALSE);
	enemies->enemy_tex = mlx_texture_to_image(mlx, tex);
	if (!enemies->enemy_tex)
		return (FALSE);
	mlx_delete_texture(tex);
	return (1);
}

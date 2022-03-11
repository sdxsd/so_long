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

#include "../include/enemy_bonus.h"

/* This function returns a random integer */
/* between int min and int max. Functions */
/* by reading 4 bytes in from the device file /dev/urandom */
/* or on Darwin /dev/random. Uses a int pointer as the */
/* "buffer" for the integer. Sets the int ret */
/* to the value of the aforementioned buffer */
/* frees the *num pointer, and returns. */
static int	get_random(int min, int max)
{
	int	fd;
	int	*num;
	int	ret;

	num = malloc(sizeof(int));
	if (!num)
		return (-1);
	if (LINUX)
		fd = open("/dev/urandom", O_RDONLY);
	else if (DARWIN)
		fd = open("/dev/random", O_RDONLY);
	else
		return (-1);
	read(fd, num, 4);
	ft_printf("RANDOM_NUMBER: %d\n", *num);
	ret = *num;
	free(num);
	return (ret % (min - max + 1) + min);
}

/* Simple function to return a non hardcoded */
/* but hopefully relatively logical limit for */
/* the number of enemies. */
static int	enemy_limit(x, y)
{
	return ((x * y) / 64);
}

/* Allocates memory for the t_enemy_db struct */
/* and enough for each enemy as defined by the */
/* enemy_count argument. Enemies are stored */
/* as an array of pointers to t_enemy types. */
t_enemy_db *alloc_enemies(int enemy_count)
{
	t_enemy_db	*enemies;
	int			iter;

	enemies = malloc(sizeof(t_enemy_db));
	while (iter < enemy_count)
	{
		enemies->e_registry[iter] = malloc(sizeof(t_enemy));
		iter++;
	}
	return (enemies);
}

/* Registers an enemy on the e_registry within the t_enemy_db */
/* struct. Sets the pointer to the enemies x, and y accordingly. */
/* Sets the enemies index in the mlx_image_t instance arrray. */
/* The static variable e_index holds the current index. */
static int	register_enemy(mlx_t mlx, t_enemy_db *enemies, int x, int y)
{
	static int	e_index;
	if (!enemies->enemy_tex)
		load_femmax(mlx, enemies);
	enemies->e_registry[e_index]->x = &enemies->enemy_tex->instances[e_index].x;
	enemies->e_registry[e_index]->y = &enemies->enemy_tex->instances[e_index].y;
	enemies->e_registry[e_index]->i_index = e_index;
	e_index++;
}

/* Handles the initialisation of the enemies within the game. Only */
/* called if compiled with bonus. First the t_enemy_db pointer */
/* is allocated and set up freshly by the alloc_enemies function. */
/* Then a loop is declared until a sufficient amount of enemies */
/* are initialised as defined by the enemy limit function */
/* which bases the limit off the dimensions of the map. */
/* The second while loop continuously generates numbers */
/* till the chosen coordinate is not a wall. */
/* The third while loop ensures that the generated numbers */
/* are not outside the bounds of the map. */
/* Once the two inner while loops have generated */
/* a suitable coordinate for the new enemy, the */
/* enemy is registered by the register_enemy() function */
/* and the process is repeated. */
static int	gen_enemies(mlx_t mlx, t_matrix *matrix)
{
	int			generated;
	int			temp_x;
	int			temp_y;
	t_enemy_db	*enemies;

	enemies = alloc_enemies(enemy_limit(matrix->x, matrix->y));
	generated = 0;
	while (generated < enemy_limit(matrix->x, matrix->y))
	{
		while (matrix->simulation_data[temp_y][temp_x] == '1')
		{
			while (temp_x < 0 && temp_y < 0)
			{
				temp_x = get_random(0, matrix->x);
				temp_y = get_random(0, matrix->y);
			}
		}
		register_enemy(mlx, enemies, temp_x, temp_y);
	}
	return (0);
}

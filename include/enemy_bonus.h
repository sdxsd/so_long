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

#ifndef ENEMY_BONUS_H
# define ENEMY_BONUS_H
# ifndef LINUX
#  define LINUX 0
# endif
# ifndef DARWIN
#  define DARWIN 0
# endif
# include "so_long.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int	gen_enemies(mlx_t *mlx, t_reality *reality);

/* Contains the basic data of representative */
/* of an enemy within the program. */
/* A pointer to the x and y positions */
/* of the enemy instance, and an integer */
/* referring to it's position in the array of */
/* instances held in the mlx_image_t struct. */
typedef struct s_enemy {
	int	*x;
	int	*y;
	int	i_index;
}	t_enemy;

/* A database containing the number of enemy instances */
/* in the program, the enemy texture, and an array */
/* holding the data of each individual enemy. */
typedef struct s_enemy_db {
	int			enemy_count;
	mlx_image_t	*enemy_tex;
	t_enemy		**e_registry;
}	t_enemy_db;

#endif // ENEMY_BONUS_H

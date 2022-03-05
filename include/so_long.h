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

#ifndef SO_LONG_H
# define SO_LONG_H
# define BLKSIZ 32
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

// Structure for holding the texture data
// represented as pointers to mlx image types.
// Part of the game data stuct s_reality.
// ASSOCIATED FUNCTIONS:
// 	load_texture()	- textures.c
// 	map_blk() 		- textures.c
// 	rndr_line()		- textures.c
typedef struct s_imgdata {
	mlx_image_t	*wall;
	mlx_image_t	*coll;
	mlx_image_t	*exit;
	mlx_image_t	*plyr;
}	t_imgdata;

// Struct for holding map data.
// Contains a width and height variable
// and two double pointers.
// Map data is stored as an array
// of char pointers. **simulation_data
// is used as a mutable index, pointing
// to the current line of map data
// being operated upon or interpreted.
// **wired_entry will always point to the
// first line of map data.
// ASSOCIATED FUNCTIONS:
// 	init_matrix()	- parse.c
//	load_map()		- parse.c
//	rndr_matrix()	- rndr_matrix.c
typedef struct s_matrix {
	int			x;
	int			y;
	char		**wired_entry;
	char		**simulation_data;
}	t_matrix;

// Struct for holding game and engine data.
// *mlx is the mlx pointer, and passed to rendering
// functions.
// plyr_x and plyr_y contains the current position of
// the player.
// *matrix contains the map data.
// *textures contains the image/sprite data.
// ASSOCIATED FUNCTIONS:
// 	init_reality()	- main.c
// 	init_matrix()	- parse.c
// 	rndr_matrix()	- rndr_matrix.c
typedef struct s_reality {
	mlx_t		*mlx;
	int			plyr_x;
	int			plyr_y;
	int			step_c;
	t_matrix	*matrix;
	t_imgdata	*textures;
}	t_reality;

#endif // SO_LONG_H

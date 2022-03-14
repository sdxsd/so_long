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

// It loads, that which it loads lingers as an eternal question
// etched upon the minds of the pitiful fool who chooses to read
// the code so lovingly curled between the damnable curly braces.
// In the swirling cerebrum of the programmer who wrote this
// function is the answer to the question of the queer meaning of such
// a function, the definition of symbol "femmax". Perhaps
// it was the alien influence of the cold void of the beyond
// that first made contact with the latter poor programmer
// who ordained this function to be written. Perhaps from man's
// first steps it was decided that this function be written, lest
// some terrible truth be uncovered as to shake all moral
// foundations that good humanity rests its cosmic hopes
// and laurels upon. Perhaps it ought to be thought upon
// that the meaning of this function is not meant to be known for human minds
// or for the minds of any thinking creature that does not comprehend
// the cosmick totality of the rituals ingrained within Ethos Programmera.
int	load_femmax(mlx_t *mlx, t_enemy_db *enemies)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(".images/femmax.png");
	if (!tex)
		return (FALSE);
	enemies->enemy_tex = mlx_texture_to_image(mlx, tex);
	if (!enemies->enemy_tex)
		return (FALSE);
	mlx_delete_texture(tex);
	return (1);
}

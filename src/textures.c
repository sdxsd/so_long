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

#include "../include/textures.h"
#include "../include/so_long.h"

/* Loads a texture indicated by argument */
/* blk from the equivalent file. */
/* Converts the texture to an mlx_image_t pointer */
/* then purges the texture from RAM */
/* before returning. */
mlx_image_t	*load_img(mlx_t *mlx, char blk)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	char			*t_path;

	if (blk == 'C')
		t_path = ft_strjoin(TEXTURE_PACK, "coll.png");
	else if (blk == 'P')
		t_path = ft_strjoin(TEXTURE_PACK, "plyr.png");
	else if (blk == '1')
		t_path = ft_strjoin(TEXTURE_PACK, "wall.png");
	else if (blk == 'E')
		t_path = ft_strjoin(TEXTURE_PACK, "exit.png");
	else
		return (NULL);
	tex = mlx_load_png(t_path);
	if (!tex)
		return (NULL);
	img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	free(t_path);
	return (img);
}

/* Loads textures into the tex_struct data structure for later use. */
/* Functions by declaring and allocating enough */
/* memory for a structure that holds the programs */
/* image data. */
/* Loads each texture by individual calls to load_img() */
/* Checks for any failures in texture loading, and then */
/* if there are no problems, returns a pointer */
/* to the struct to the calling function. */
/* If allocated with malloc(sizeof(img_struct)) then */
/* a heap based buffer overflow will occur. */
t_imgdata	*load_textures(mlx_t *mlx)
{
	t_imgdata	*img_struct;

	img_struct = malloc(sizeof(mlx_image_t *) * 4);
	if (!img_struct)
		return (NULL);
	img_struct -> wall = load_img(mlx, '1');
	img_struct -> coll = load_img(mlx, 'C');
	img_struct -> exit = load_img(mlx, 'E');
	img_struct -> plyr = load_img(mlx, 'P');
	if (!img_struct -> wall || !img_struct -> coll
		|| !img_struct -> exit || !img_struct -> plyr)
		return (NULL);
	return (img_struct);
}

/* Simple mapping function */
/* Takes a t_imgdata pointer and a blk */
/* returns the image associated with blk from the */
/* t_imgdata struct to the calling function */
/* If input is invalid (such as '0') returns NULL */
mlx_image_t	*map_blk(t_imgdata *textures, char blk)
{
	if (blk == '1')
		return (textures -> wall);
	else if (blk == 'C')
		return (textures -> coll);
	else if (blk == 'E')
		return (textures -> exit);
	else
		return (NULL);
}

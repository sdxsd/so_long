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

/* All things repeat in echo of eachother. */

#include "../include/game.h"
#include "../include/dealloc.h"
#ifdef BONUS
#  include "../include/femmax_bonus.h"
#endif

/* The val_move() function takes the x, and y coordinates */
/* that the player will be at due to the given keypress in handle_key() */
/* and simply checks if the player is not moving into a wall. */
/* If the player would be moving into a wall, the function returns */
/* false, or invalid input. */
int	val_move(int x, int y, t_matrix *matrix)
{
	matrix->simulation_data = matrix->wired_entry;
	if (matrix->simulation_data[y / BLKSIZ][x / BLKSIZ] == '1')
		return (FALSE);
	return (TRUE);
}

/* This function checks the position of the player against the map */
/* and takes actions accordingly. */
/* if the current player position falls on a collectible, */
/* the following occurs. Sets a current_haring int */
/* which refers to the index of the */
/* instance array in the coll image */
/* held by the textures struct. */
/* Then two pointers, one to the x of the current instance, */
/* and the other to the y. Sets the x of the haring instance */
/* to the current haring_basket_pos. */
/* And then the y to 0 (referring to the first row). */
/* The position on the map (formerly a collectible tile) is set to a blank. */
/* The offset of the haring */
/* (intended to create a stacking effect) is incremented by 15. */
/* Otherwise, if the player is on an exit, */
/* and all the collectibles have been collected */
/* the programs memory is deallocated and the program exits. */
static int	check_pos(t_reality *reality, int x, int y)
{
	int			curr_haring;
	int			*haring_x;
	int			*haring_y;
	static int	haring_basket_pos;

	if (reality->matrix->simulation_data[y][x] == 'C')
	{
		curr_haring = reality->haring_db->haring_data[y][x];
		haring_x = &reality->textures->coll->instances[curr_haring].x;
		haring_y = &reality->textures->coll->instances[curr_haring].y;
		*haring_x = haring_basket_pos;
		*haring_y = 0;
		reality->matrix->coll_c++;
		reality->matrix->simulation_data[y][x] = '0';
		haring_basket_pos += 15;
	}
	if (reality->matrix->simulation_data[y][x] == 'E')
	{
		if (reality->matrix->coll_c >= reality->haring_db->haring_c)
		{
			ft_putstr("You win!\n");
			free_and_exit(reality);
		}
	}
	return (TRUE);
}

/* This function handles actions based on what key */
/* is pressed. A number of convenience variables are */
/* set to reduce the length of lines. The val_move() function */
/* is passed used in every if to validate if a movement is valid */
/* in the game.
   Then the requisite changes are made to the player coordinates. */
/* check_pos() is then used to make any changes to game state */
/* based on the current position of the player. */
/* After that, current steps are printed out and the function returns. */
static void	handle_key(char key, t_reality *reality)
{
	int			*plyr_x;
	int			*plyr_y;
	t_matrix	*mtrx;

	mtrx = reality -> matrix;
	plyr_x = &reality->matrix->plyr_x;
	plyr_y = &reality->matrix->plyr_y;
	if (key == 'W' && val_move(*plyr_x, *plyr_y - BLKSIZ, mtrx))
		*plyr_y -= BLKSIZ;
	else if (key == 'A' && val_move(*plyr_x - BLKSIZ, *plyr_y, mtrx))
		*plyr_x -= BLKSIZ;
	else if (key == 'S' && val_move(*plyr_x, *plyr_y + BLKSIZ, mtrx))
		*plyr_y += BLKSIZ;
	else if (key == 'D' && val_move(*plyr_x + BLKSIZ, *plyr_y, mtrx))
		*plyr_x += BLKSIZ;
	check_pos(reality, *plyr_x / BLKSIZ, *plyr_y / BLKSIZ);
	ft_printf("STEPS: %d\n", reality->matrix->step_c++);
	return ;
}

/* This function handles input from the keyboard. */
/* Takes a pointer to *param, aka the reality struct */
/* (which stores all program data). Defines a keydictionary */
/* of recognized and valid keyboard input. If the action of the keydata */
/* is the press, the keydata is checked to make sure it falls within */
/* the set of valid characters. If it is, then it is passed to the */
/* handle_key() function, along with the t_reality* pointer. */
/* Otherwise, if the key is ESC, then the entire program is freed, */
/* and promptly exits. */
/* Then the rndr_matrix() function is called to update the player */
/* position once handle_key() has resolved. */
static void	keycodes(mlx_key_data_t keydata, void *param)
{
	t_reality	*reality;
	const char	*keydict = "WASD";

	reality = param;
	if (keydata.action == MLX_PRESS)
	{
		if (ft_charchk(keydata.key, (char *)keydict))
			handle_key(keydata.key, reality);
		else if (keydata.key == MLX_KEY_ESCAPE)
			free_and_exit(reality);
		if (BONUS)
			gen_enemies(reality->mlx, reality);
	}
	rndr_matrix(reality);
	return ;
}

/* The basic gameloop functions, first sets the mlx_key_hook */
/* to the keycodes function, before entering the mlx_loop. */
int	gameloop(t_reality *reality)
{
	mlx_key_hook(reality -> mlx, keycodes, reality);
	mlx_loop(reality->mlx);
	return (TRUE);
}

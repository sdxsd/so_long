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

#include "../include/parse.h"
#include "../include/so_long.h"
#include "../include/dealloc.h"

/* valline() (short for validate line) */
/* takes the y position of the given line, */
/* and checks for validity of the line */
/* based on said position. */
/* The variable fir_lst (first last) */
/* defines the acceptable characters that can be present */
/* in the first and last line of the map. */
/* If the value of y is -1 */
/* this indicates the last line of the map data. */
/* This function simply iterates through a line */
/* passing each character to a subroutine */
/* that checks the given character against a dictionary */
/* of characters in the form of a char pointer. */
/* Returns false if ft_charchk() fails */
/* at any time. */
static int	valline(char *line, int y)
{
	const char	*fir_lst = "1\n";
	int			iterator;

	iterator = 0;
	if (y == 0 || y == -1)
	{
		while (line[iterator] != '\0')
		{
			if (!ft_charchk(line[iterator], (char *)fir_lst))
				return (FALSE);
			iterator++;
		}
	}
	return (TRUE);
}

/* chline() (check line) takes a line of map data */
/* represented as a char pointer, a length value */
/* represented as x, and the current y value pertaining */
/* to the line provided. */
/* The dict variable defines acceptable characters within the map. */
/* If the strlen() of line does not equal the x value */
/* given, then the line is invalid, as lines must all be of */
/* equal width. */
/* The function then simply iterates through the line */
/* while running the ft_charchk() function which compares */
/* a given character to see if it contains any */
/* characters outside of the provided set. */
/* Continuing, the function runs the valline() function */
/* which validates the line based on the given y position. */
/* If any of the checks fail, the line is freed, and false is returned. */
/* Otherwise the function returns true. */
static int	chline(char *line, int x, int y, t_matrix *matrix)
{
	const char	*dict = "01CEP\n";
	int			iterator;

	iterator = 0;
	if ((int)ft_strlen(line) != x)
	{
		free(line);
		return (FALSE);
	}
	while (iterator < x)
	{
		if (!ft_charchk(line[iterator], (char *)dict))
		{
			free(line);
			return (FALSE);
		}
		if (line[iterator] == 'P')
		{
			matrix -> plyr_x = iterator * 32;
			matrix -> plyr_y = y * 32;
		}
		iterator++;
	}
	if (!valline(line, y))
	{
		free (line);
		return (FALSE);
	}
	return (TRUE);
}

/* This function validates the map, returning 1 (TRUE) if */
/* the map passes validity checks. */
/* Functions by defining an iterative variable */
/* referencing the current y position */
/* when indexing the map data. */
/* **simulation_data is set to **wired_entry */
/* with the latter pointing to the first */
/* element of the map data, loaded as an array */
/* of strings. */
/* While the variable iter_y does not yet */
/* equal the total rows (y value) of the map */
/* then the following is executed. */
/* The function chline() (short for check line) */
/* is provided the current row being indexed, */
/* the line of map data associated with the */
/* aforementioned row, and the length of the row */
/* being represented as the x value. */
/* If the function does not return TRUE */
/* then false is returned and the validation fails. */
/* Otherwise the function continues, incrementing */
/* the iter_y value and moving down a row */
/* in simulation_data. */
static int	validate_map(t_matrix *matrix)
{
	int	iter_y;

	iter_y = 0;
	matrix -> simulation_data = matrix -> wired_entry;
	while (iter_y < matrix -> y)
	{
		if (!chline(*matrix -> simulation_data, matrix -> x, iter_y, matrix))
			return (FALSE);
		matrix -> simulation_data++;
		iter_y++;
	}
	return (TRUE);
}

/* Loads the map into memory for later parsing. */
/* Returns null on failure. */
/* Functions by defining a starting pointer (wired_entry) */
/* and a index pointer (simulation_data) */
/* index pointer is iterated upon while */
/* loading file line by line. */
/* starting pointer points to the first element in the */
/* index pointer. */
/* if get_next_line() does not return a line */
/* the function checks if there has been any line */
/* found. If true, then the loop is broken. */
/* If there isn't a line, and no line */
/* has been loaded, the function returns null. */
static t_matrix	*load_map(char *path, t_matrix *matrix)
{
	char	*line;
	int		fd;

	matrix -> simulation_data = malloc(sizeof(char *) * 1024);
	matrix -> wired_entry = matrix -> simulation_data;
	matrix -> x = -1;
	matrix -> y = 0;
	fd = open(path, O_RDONLY);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (matrix -> x == -1)
				matrix -> x = ft_strlen(line);
			*matrix -> simulation_data = line;
			matrix -> simulation_data++;
			matrix -> y++;
		}
		else if (!line && *matrix -> wired_entry != NULL)
			break ;
		else
			return (NULL);
	}
	return (matrix);
}

/* Initiates basic input checking before */
/* passing the map parsing to subroutines. */
/* Functions by defining a pointer to a t_matrix */
/* which will eventually hold the map data */
/* and other necessary data such as the */
/* width and height. Then operates basic argument */
/* checking and returns NULL if the arguments are */
/* insufficient. Allocates memory for the t_matrix */
/* struct. Runs the load map function, */
/* which loads the map into memory and */
/* defines the map dimensions. */
/* Then runs the validate_map() function */
/* to validate that the aforementioned */
/* map_data constitutes a valid map */
/* according to the project definitions. */
/* Finally returns the populated Matrix struct. */
t_matrix	*matrix_init(int argc, char *argv[])
{
	t_matrix	*matrix;

	if (argc < 2 || argv[1] == NULL)
		return (NULL);
	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->coll_c = 0;
	if (!load_map(argv[1], matrix))
		return (free_matrix(matrix));
	if (!validate_map(matrix))
		return (free_matrix(matrix));
	matrix -> x--;
	return (matrix);
}

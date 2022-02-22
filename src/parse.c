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

static int	valline(char *line, int y)
{
	const char	*firlst = "1\n";
	int			iterator;

	iterator = 0;
	if (y == 0)
	{
		while (line[iterator] != '\0')
		{
			if (!ft_charchk(line[iterator], (char *)firlst))
				return (0);
			iterator++;
		}
	}
	return (1);
}

static int	chline(char *line, int x, int y)
{
	const char	*dict = "01CEP\n";
	int	iterator;

	iterator = 0;
	if ((int)ft_strlen(line) != x)
	{
		free(line);
		return (0);
	}
	while (iterator < x)
	{
		if (!ft_charchk(line[iterator], (char *)dict))
		{
			free(line);
			return (0);
		}
		if (!valline(line, y))
		{
			free (line);
			return (0);
		}
		iterator++;
	}
	return (1);
}

static t_the_matrix* 	chmap_val(char *path, t_the_matrix* matrix)
{
	int		temp_x;
	char	*line;
	int		fd;

	temp_x = -1;
	fd = open(path, O_RDONLY);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (temp_x == -1)
				temp_x = ft_strlen(line);
			if (!chline(line, temp_x, matrix -> y))
				return (NULL);
			else
				matrix -> y++;
			free(line);
		}
		else if (matrix -> y != 0)
			break ;
		else
			return (NULL);
	}
	matrix -> x = temp_x;
	return (matrix);
}


t_the_matrix*	matrix_init(int argc, char *argv[])
{
	t_the_matrix *matrix;

	if (argc < 2 || argv[1] == NULL)
		return (NULL);
	matrix = malloc(sizeof(t_the_matrix));
	if (!matrix)
		return (NULL);
	if (!chmap_val(argv[1], matrix))
	{
		free(matrix);
		return (NULL);
	}
	return (matrix);
}

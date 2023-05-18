/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:23:39 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/17 19:44:00 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_space(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' 
		|| c == '\f' || c == '\r' || c == 4)
		return (1);
	return (0);
}

int is_valid(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_cross(char **map, int i, int j)
{	
	if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1] || !map[i - 1][j] || !map[i + 1][j])
		return (0);
	if (!is_valid(map[i][j + 1]) || !is_valid(map[i][j - 1]) || !is_valid(map[i + 1][j])
		|| !is_valid(map[i - 1][j]))
		return (0);
	return (1);
}

int	count_lines(const char *filename)
{
	char	c;
	int		fd;
	int		line_count;
	int		bytes_read;

	line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (c == '\n')
		{
			line_count++;
		}
		bytes_read = read(fd, &c, 1);
	}
	close(fd);
	return (line_count);
}

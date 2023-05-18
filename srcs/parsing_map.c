/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:00:43 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/17 19:59:43 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	**get_map(char **file)
{
	char	**map;
	int		i;
	int		j;
	int		start_line;
	
	i = 0;
	start_line = 0;
	while (file[i])
	{
		if (!ft_strncmp(file[i], "NO", 2) || !ft_strncmp(file[i], "SO", 2)
			|| !ft_strncmp(file[i], "WE", 2) || !ft_strncmp(file[i], "EA", 2) 
			||  !ft_strncmp(file[i], "F ", 2) || !ft_strncmp(file[i], "C ", 2) || file[i][0] == '\n')
				start_line++;		
		i++;
	}
	map = malloc(sizeof(char *) * (i - start_line + 1));
	if (!map)
		return (NULL);
	j = 0;
	while (file[start_line] && start_line <= i)
	{
		map[j] = ft_strdup(file[start_line]);
		start_line++;
		j++;
	}
	map[j] = 0;
	return (map);
}

// Check si la map est compose que de 0, 1, 2, N, S, E, W, ' '.

static int	is_valid_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(" 01NSEW\n", map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// Check if the card is locked
static int	is_close(char **map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("0NSEW", map[i][j]))
			{
				if (i == 0 || i == ft_strlen(map[i]) - 1)
					return (0);
				if (j == 0 || j == ft_strlen(map[i]) - 1)
					return (0);
				if (check_cross(map, i, j) == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_player(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (0);
	return (1);
}

bool	is_valid_map(t_map *data)
{
	if (!is_valid_char(data->map))
		return (false);
	if (!is_close(data->map))
		return (false);
	if (!check_player(data->map))
		return (false);
	return (true);
}

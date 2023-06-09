/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoire <gregoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:00:43 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/21 18:22:40 by gregoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
					return (printf("4\n"), 0);
				if (j == 0 || j == ft_strlen(map[i]) - 1)
					return (printf("5\n"), 0);
				if (check_cross(map, i, j) == 0)
					return (printf("6\n"), 0);
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
		return (printf("1\n"), false);
	if (!is_close(data->map))
		return (printf("2\n"), false);
	if (!check_player(data->map))
		return (printf("3\n"), false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:00:43 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/17 15:41:44 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	**get_map(char **file)
{
	int	i;
	int j;
	char **map;
	
	i = 0;
	j = 0;
	while (file[i])
	{
		if (ft_strncmp(file[i], "NO", 2) || ft_strncmp(file[i], "SO", 2)
			|| ft_strncmp(file[i], "WE", 2) 
			|| ft_strncmp(file[i], "EA", 2) 
			|| ft_strncmp(file[i], "F", 1), ft_strncmp(file[i], "C", 1))
				i++;
		else
		{
			j++;
			i++;
		}
	}
	map = malloc(sizeof(char *) * (j + 1));
	if (!map)
		return (ft_putstr_fd("Error : malloc fail\n", 2), NULL);
	i = 0;
	j = 0;
	while (file[i])
	{
		
		if (!ft_strncmp(file[i], "NO", 2) || !ft_strncmp(file[i], "SO", 2) 
			|| !ft_strncmp(file[i], "WE", 2) 
			|| !ft_strncmp(file[i], "EA", 2) 
			|| !ft_strncmp(file[i], "F", 1) || !ft_strncmp(file[i], "C", 1))
			{
				printf("tessajdbusajhbast i = %d\n", i);
				i++;
			}
		else
		{   
			printf("test i = %d\n", i);
			map[j] = ft_strdup(file[i]);
			j++;
			i++;
		}
	}
	return (map);
}

// Check si la map est compose que de 0, 1, 2, N, S, E, W, ' '.

static int is_valid_char(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(" 01NSEW", map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


// check isspace et proteger les cases vides
static int is_close(char **map)
{
	unsigned int i;
	unsigned int j;

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

bool is_valid_map(t_map *data)
{
	if (!is_valid_char(data->map))
		return (false);
	if (!is_close(data->map))
		return (false);
	return (true);
}

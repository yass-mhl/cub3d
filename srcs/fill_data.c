/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:46:17 by ymehlil           #+#    #+#             */
/*   Updated: 2023/06/10 15:18:29 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char *ft_strtokstr(char *str, char *sep)
{
	int		i;
	int		index_sep;
	char	*tmp;
	char 	*res;

	i = 0;
	index_sep = ft_strstr(str, sep);
	if (index_sep == -1)
		return (NULL);
	index_sep += ft_strlen(sep);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - index_sep + 1));
	if (!tmp)
		return (NULL);
	while (str[index_sep + i])
	{
		tmp[i] = str[index_sep + i];
		i++;
	}
	tmp[i] = '\0';
	res = ft_strtrim(tmp, " ");
	return (free(tmp), res);
}

char *get_identifier(char **file, char *identifier)
{
	int		i;
	char	*res;
	char 	*tmp;
	char	*tmp2;
	
	i = 0;
	while (file[i] && ft_strncmp(file[i], identifier, ft_strlen(identifier)))
		i++;
	tmp = ft_strtokstr(file[i], identifier);
	tmp2 = ft_strtrim(tmp, " ");
	res = ft_strtrim(tmp2, "\n");
	return (free(tmp), free(tmp2), res);
}

int get_pos(char **map, char pos)
{
	int	i;
	int j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (pos == 'x')
					return (j);
				else if (pos == 'y')
					return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

char get_orientation(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				return (map[i][j]);
			j++;
		}
	}
	return (-1);
}

double get_dir(char orientation, char c)
{
	if (c == 'x')
	{
		if (orientation == 'N')
			return (0);
		else if (orientation == 'S')
			return (0);
		else if (orientation == 'E')
			return (1);
		else if (orientation == 'W')
			return (-1);
	}
	else if (c == 'y')
	{
		if (orientation == 'N')
			return (1);
		else if (orientation == 'S')
			return (-1);
		else if (orientation == 'E')
			return (0);
		else if (orientation == 'W')
			return (0);
	}
}

double get_plane(char orientation, char c)
{
	if (c == 'x')
	{
		if (orientation == 'N')
			return (0.66);
		else if (orientation == 'S')
			return (-0.66);
		else if (orientation == 'E')
			return (0);
		else if (orientation == 'W')
			return (0);
	}
	else if (c == 'y')
	{
		if (orientation == 'N')
			return (0);
		else if (orientation == 'S')
			return (0);
		else if (orientation == 'E')
			return (0.66);
		else if (orientation == 'W')
			return (-0.66);
	}
}

t_config	*set_config(t_map *data)
{
	t_config	*config;
	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	// config->map = data->map;
	config->no = get_identifier(data->file, "NO");
	config->so = get_identifier(data->file, "SO");
	config->we = get_identifier(data->file, "WE");
	config->ea = get_identifier(data->file, "EA");
	config->f = get_identifier(data->file, "F ");
	config->c = get_identifier(data->file, "C ");
	config->player_pos_x = get_pos(data->map, 'x');
	config->player_pos_y = get_pos(data->map, 'y');
	config->player_orientation = get_orientation(data->map);
	config->dir_x = get_dir(config->player_orientation, 'x');
	config->dir_y = get_dir(config->player_orientation, 'y');
	config->plane_x = get_plane(config->player_orientation, 'x');
	config->plane_y = get_plane(config->player_orientation, 'y');
	return (config);
	
}

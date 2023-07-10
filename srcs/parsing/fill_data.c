/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:46:17 by ymehlil           #+#    #+#             */
/*   Updated: 2023/07/10 18:12:11 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_pos(char **map, char pos)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (pos == 'x')
					return ((double)j);
				else if (pos == 'y')
					return ((double)i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

char	get_orientation(char **map)
{
	int	i;
	int	j;

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
		i++;
	}
	return (-1);
}

double	get_dir(char orientation, char c)
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
			return (-1);
		else if (orientation == 'S')
			return (1);
		else if (orientation == 'E')
			return (0);
		else if (orientation == 'W')
			return (0);
	}
	return (1);
}

double	get_plane(char orientation, char c)
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
	return (1);
}

void	set_config(t_map *data, t_config *config)
{
	config->no = get_identifier(data->file, "NO");
	config->so = get_identifier(data->file, "SO");
	config->we = get_identifier(data->file, "WE");
	config->ea = get_identifier(data->file, "EA");
	config->f = get_identifier(data->file, "F ");
	config->c = get_identifier(data->file, "C ");
	config->p_pos_x = get_pos(data->map, 'x');
	config->p_pos_y = get_pos(data->map, 'y');
	config->player_orientation = get_orientation(data->map);
	config->dirx = get_dir(config->player_orientation, 'x');
	config->diry = get_dir(config->player_orientation, 'y');
	config->plane_x = get_plane(config->player_orientation, 'x');
	config->plane_y = get_plane(config->player_orientation, 'y');
	config->hexa_f = rgb_to_hex(config->f);
	config->hexa_c = rgb_to_hex(config->c);
	config->h = TEXHEIGHT;
	config->w = TEXWIDTH;
	config->textures = NULL;
	config->mlx = NULL;
	config->pixelMap = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:34:06 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/18 18:14:16 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	**get_file(char *filename)
{
	int		fd;
	int		i;
	int		nb_line;
	char	**all_lines;

	i = -1;
	nb_line = count_lines(filename);
	all_lines = malloc(sizeof(char *) * (nb_line + 1));
	if (!all_lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (ft_free_all_tab(all_lines, nb_line), NULL);
	while (++i < nb_line)
	{
		all_lines[i] = get_next_line(fd);
		if (!all_lines[i])
			return (ft_free_all_tab(all_lines, i), NULL);
	}
	all_lines[i] = 0;
	return (close(fd), all_lines);
}

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
			|| !ft_strncmp(file[i], "F ", 2) || !ft_strncmp(file[i], "C ", 2)
			|| file[i][0] == '\n')
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
		map[j] = ft_strtrim(map[j], "\n");
		start_line++;
		j++;
	}
	map[j] = 0;
	return (map);
}
void replace_spaces_with_one(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ')
                map[i][j] = '1';
            j++;
        }
        i++;
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
	config->player_orientation = 0;
	return (config);
	
}

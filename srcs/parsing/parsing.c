/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:34:06 by ymehlil           #+#    #+#             */
/*   Updated: 2023/07/20 15:36:42 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_file(char *filename)
{
	int		fd;
	int		i;
	int		nb_line;
	char	**all_lines;
	char	*last_line;

	i = -1;
	nb_line = count_lines(filename);
	all_lines = malloc(sizeof(char *) * (nb_line + 1));
	if (!all_lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (ft_free_all_tab(all_lines), NULL);
	while (++i < nb_line)
	{
		all_lines[i] = get_next_line(fd);
		if (!all_lines[i])
			return (ft_free_all_tab(all_lines), NULL);
	}
	last_line = get_next_line(fd);
	if (last_line)
		free(last_line);
	all_lines[i] = 0;
	return (close(fd), all_lines);
}

int	count_start_line(char **file)
{
	int	i;
	int	start_line;
	int	j;

	i = 0;
	start_line = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] && file[i][j] == ' ')
			j++;
		if (!ft_strncmp(&file[i][j], "NO", 2) || !ft_strncmp(&file[i][j], "SO",
				2) || !ft_strncmp(&file[i][j], "WE", 2)
			|| !ft_strncmp(&file[i][j], "EA", 2) || !ft_strncmp(&file[i][j],
				"F ", 2) || !ft_strncmp(&file[i][j], "C ", 2)
			|| file[i][0] == '\n')
			start_line++;
		i++;
	}
	return (start_line);
}

char	**get_map(char **file)
{
	char	**map;
	int		i;
	int		j;
	int		start_line;
	char	*tmp;

	start_line = count_start_line(file);
	i = 0;
	while (file[i])
		i++;
	map = malloc(sizeof(char *) * (i - start_line + 1));
	if (!map)
		return (NULL);
	j = 0;
	while (file[start_line] && start_line <= i)
	{
		tmp = ft_strdup(file[start_line]);
		map[j] = ft_strtrim(tmp, "\n");
		start_line++;
		j++;
		free(tmp);
	}
	map[j] = NULL;
	return (map);
}

void	replace_spaces_with_one(char **map)
{
	int	i;
	int	j;

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

bool	check_config(t_config *config)
{
	if (!config->no || !config->so || !config->we || !config->ea || !config->f
		|| !config->c)
		return (false);
	if (!check_f_c(config) || !check_commas(config->f)
		|| !check_commas(config->c))
		return (false);
	if (config->hexa_f == -1 || config->hexa_c == -1)
		return (false);
	if (!check_path(config->no) || !check_path(config->so)
		|| !check_path(config->we) || !check_path(config->ea))
		return (false);
	return (true);
}

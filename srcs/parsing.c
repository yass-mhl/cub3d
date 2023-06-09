/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoire <gregoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:34:06 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/26 05:04:01 by ymehlil          ###   ########.fr       */
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
	char 	*tmp;

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
		tmp = ft_strdup(file[start_line]);
		map[j] = ft_strtrim(tmp, "\n");
		start_line++;
		j++;
		free(tmp);
	}
	map[j] = NULL;
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

static int check_path(char *path)
{
	// En gros peut etre jsp a doit quoi ressembler le path si c'est un dossier ou un fichier
	// int fd;

	// fd = open(path, O_RDONLY);
	// if (fd <= 0)
	// 	return (false);
	// close(fd);
	// return (true);
	if (!is_directory_is_valid(path))
		return (0);
	return (1);
}

bool	check_config(t_config *config)
{
	if (!config->no || !config->so || !config->we || !config->ea
		|| !config->f || !config->c)
		return (false);
	if (!check_f_c(config) || !check_commas(config->f) || !check_commas(config->c))
		return (false);
	if (!check_path(config->no) || !check_path(config->so)
		|| !check_path(config->we) || !check_path(config->ea))
		return (false);
	return (true);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:00:09 by ymehlil           #+#    #+#             */
/*   Updated: 2023/07/05 16:59:37 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_nb_infos(char **file)
{
	int		i;
	t_check	check;

	i = 0;
	ft_fill_check(&check);
	while (file[i])
	{
		if (ft_strncmp(file[i], "NO", 2) == 0)
			check.no += 1;
		else if (ft_strncmp(file[i], "SO", 2) == 0)
			check.so += 1;
		else if (ft_strncmp(file[i], "WE", 2) == 0)
			check.we += 1;
		else if (ft_strncmp(file[i], "EA", 2) == 0)
			check.ea += 1;
		else if (ft_strncmp(file[i], "F ", 2) == 0)
			check.f += 1;
		else if (ft_strncmp(file[i], "C ", 2) == 0)
			check.c += 1;
		i++;
	}
	if (check.no == 1 && check.so == 1 && check.we == 1 && check.ea == 1
		&& check.f == 1 && check.c == 1)
		return (1);
	return (0);
}

static int	check_valid_id(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (!file[i] || !is_space(file[i][0]))
		{
			if (ft_strncmp(file[i], "NO", 2) && ft_strncmp(file[i], "SO", 2)
				&& ft_strncmp(file[i], "WE", 2) && ft_strncmp(file[i], "EA", 2)
				&& ft_strncmp(file[i], "F ", 2) && ft_strncmp(file[i], "C ", 2)
				&& ft_strncmp(file[i], "1", 1) && ft_strncmp(file[i], "0", 1))
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_directory_is_valid(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	return (close(fd), 1);
}

int	check_cub_extension(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 3)
		return (0);
	if (file[i - 1] == 'b' && file[i - 2] == 'u' && file[i - 3] == 'c' && file[i
			- 4] == '.')
		return (1);
	return (0);
}

bool	check_args(t_map *data)
{
	if (!check_nb_infos(data->file) || !check_valid_id(data->file))
		return (false);
	return (true);
}

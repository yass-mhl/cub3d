/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:00:09 by ymehlil           #+#    #+#             */
/*   Updated: 2023/05/17 14:00:16 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char **get_file(char *map_path)
{
	int fd;
	char *line;
	char *tmp;
	char *map_str;
	char **map;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error : open fail\n", 2), NULL);
	line = get_next_line(fd);
	while (line > 0)
	{
		tmp = map_str;
		map_str = ft_strjoin(map_str, line);
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
	map = ft_split(map_str, '\n');
	free(map_str);
	if (!map)
		return (ft_putstr_fd("Error : malloc fail\n", 2), NULL);
	return (map);
}

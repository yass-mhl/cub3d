#include "cube3d.h"


// separer la map du file
char **get_map(char *map_path)
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

int check_map(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			j++;
		}
	}
	return (0);
}

char **parse_map(char *map_path)
{
	char **map;

	map = get_map(map_path);
	if (!map)
		return (NULL);
	check_map(map);
	return (map);
}

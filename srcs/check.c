# include "cube3d.h"

// static bool limit_line(int *line, int *begin, int *end)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] == -1)
// 		i++;
// 	if (i != 1)
// 		return (false);
// 	while (line[i] == 1)
// 		i++;
// 	*begin = i - 1;
// 	while (line[i])
// 		i++;
// 	while (line[i] == -1)
// 		i--;
// 	if (i != 1)
// 		return (false);
// 	while (line[i] == 1)
// 		i--;
// 	*end = i + 1;
// 	return (true);
// }


// static bool check_walls(int **map)
// {
// 	int	i;
// 	int	prev_begin;
// 	int	prev_end;
// 	int	begin;
// 	int	end;

// 	i = 0;
// 	prev_begin = 0;
// 	prev_end = 0;
// 	while (map[i])
// 	{
// 		if(limit_line(map[i], &begin, &end) == false)
// 			return (false);
// 		if(begin > prev_begin + 1 || end < prev_end - 1)
// 			return (false);
// 		i++;
// 		prev_begin = begin;
// 		prev_end = end;
// 	}
// 	return (true);
// }

// bool   check_map(char **map)
// {
// 	return (true);
// }
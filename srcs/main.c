/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoire <gregoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:54 by ymehlil           #+#    #+#             */
/*   Updated: 2023/06/08 15:13:46 by gregoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

// static bool parsing(int ac, char **av, t_map *data, t_config *config)
// {
// 	if (ac != 2)
// 		return (printf("Error 1\n"), false);
// 	if (!check_cub_extension(av[1]))
// 		return (printf("Error 2\n"), false);
// 	if (!is_directory_is_valid(av[1]))
// 		return (printf("Error 3\n"), false);
// 	data->file = get_file(av[1]);
// 	data->map = get_map(data->file);
// 	if (!data->map)
// 		return (printf("erreur data->map"), false);
// 	if (!check_args(data) || !is_valid_map(data))
// 		return (printf("Error 4\n"), false);
// 	replace_spaces_with_one(data->map);
// 	config = set_config(data);
// 	if (!check_config(config))
// 		return (printf("Error 5\n"), false);
// 	return (true);
// }

// t_scene *init_scene()
// {
// 	t_scene *scene;
// 	scene = malloc(sizeof(t_scene));
// 	if(!scene)
// 		return (printf("Error malloc scene\n"), NULL);
// 	scene->config = malloc(sizeof(t_config));
// 	if(!scene->config)
// 		return (printf("Error malloc scene->config\n"), NULL);
// 	scene->config->map = malloc(sizeof(t_map));
// 	if(!scene->config->map)
// 		return (printf("Error malloc scene->config->map\n"), NULL);
// 	return (scene);
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	t_scene *scene;
// 	scene = init_scene();
// 	// if(!scene)
// 	// 	return (1);
// 	// if (!parsing(ac, av, scene->config->map, scene->config))
// 	// 	return (2);
// 	int i = 0;
// 	scene->config->map->map = get_map(get_file(av[1]));
// 	while (scene->config->map->map[i])
// 	{
// 		printf("%s\n",scene->config->map->map[i]);
// 		i++;
// 	}
// 	render(scene); 
// 	return (0);
// }

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int main(int ac, char **av)
{
	////////////////////////
	int **worldMap = malloc(24 * sizeof(int *));

	for(int i = 0; i < mapHeight; i++) {
		worldMap[i] = malloc(mapWidth * sizeof(int));
	}

	int tempWorldMap[mapWidth][mapHeight]=
	{
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	};

	for(int i = 0; i < mapHeight; i++) {
		for(int j = 0; j < mapWidth; j++) {
			worldMap[i][j] = tempWorldMap[i][j];
		}
	}
	////////////////////////
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
	int **map;
	map = raycast(worldMap, posX, posY, dirX, dirY, planeX, planeY);
	render(map, posX, posY, dirX, dirY, planeX, planeY);
	(void) ac;
	(void) av;
//   	void	*mlx;
// 	void	*mlx_win;
//   t_mlximg	mlx_img;
	
// 	mlx = mlx_init();
// 	if(!mlx)
// 		printf("Error mlx_init\n");
// 	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
// 	if(!mlx_win)
// 		printf("Error mlx_new_window\n");
// 	mlx_img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	if(!mlx_img.img)
// 		printf("Error mlx_new_image\n");
// 	mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel, &mlx_img.line_length,
// 								&mlx_img.endian);	
// 	printf("heeey\n");
// 	mlx_put_image_to_window(mlx, mlx_win, mlx_img.img, 0, 0);
// 	mlx_loop(mlx);
}

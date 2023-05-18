# include "cube3d.h"



void	*display_minimap(t_config *config)
{
	char **map;
	int x;
	int y;
	void	*mlx;
	void	*mlx_win;
	t_mlximg	mlx_img;

	map = config->map->map;
	x = 0;
	y = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "Cub3D");
	mlx_img.img = mlx_new_image(mlx, WINDOW_HEIGHT, WINDOW_WIDTH);
	mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel, &mlx_img.line_length,
								&mlx_img.endian);
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(map[y][x] == '1')
				my_mlx_pixel_put(mlximg, x * 10, y * 10, 0x00FF0000);
			else
				my_mlx_pixel_put(mlximg, x + 10, y * 10,  0x0000FF00);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, mlx_img.img, 0, 0);
	mlx_loop(mlx);
}

t_scene	*raycast(t_config *config)
{
	t_scene	*scene;

	scene = malloc(sizeof(*t_slice) * WINDOW_WIDTH + 1);
	if (!scene)
		return (NULL);
	

	return (scene);
}
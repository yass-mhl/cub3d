# include "cube3d.h"

void	my_mlx_pixel_put(t_mlximg *mlximg, int x, int y, int color)
{
	char	*dst;

	dst = mlximg->addr + (y * mlximg->line_length + x * (mlximg->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_column(t_slice *column, int index, t_scene *scene) 
{
    int slice;
	int y;

	slice = 0;
	while (column[slice])
	{
		y = column[slice].start;
		while(y < column[slice].end)
		{
			my_mlx_pixel_put(&scene->mlx_img, index, y, column[slice].texture);
			y++;
		}
		slice++;
	}
}

void draw_scene(t_scene *scene) 
{
	if (!scene)
		return ;

	int y;
	
	y = 0;
    while (y < scene->nb_columns) 
	{
        draw_column(scene->column[y], y, scene);
		y++;
    }
}

// Cette fonction est appelée pour commencer le rendu
void render(t_scene *scene) 
{
    // code pour préparer le rendu ici...
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cub3D");
	scene->mlx_img.img = mlx_new_image(mlx, 1920, 1080);
	scene->mlx_img.addr = mlx_get_data_addr(scene->mlx_img.img, &scene->mlx_img.bits_per_pixel, &scene->mlx_img.line_length,
								&scene->mlx_img.endian);
	draw_scene(scene);
	mlx_put_image_to_window(mlx, mlx_win, scene->mlx_img.img, 0, 0);
	mlx_loop(mlx);

    // code pour finaliser le rendu ici...
}

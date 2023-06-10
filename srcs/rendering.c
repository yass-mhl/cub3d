#include "cube3d.h"

void	my_mlx_pixel_put(t_mlximg *mlximg, int x, int y, int color)
{
	char	*dst;

	dst = mlximg->addr + (y * mlximg->line_length + x * (mlximg->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	draw_scene(int **map, void *mlx, void *mlx_win, t_mlximg *mlx_img) 
{
	int y;
	int x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (map[y][x] == -1)
			{
				if(y > WINDOW_HEIGHT / 2)
					my_mlx_pixel_put(mlx_img, x, y, 0xC8FFB4);
				else 
					my_mlx_pixel_put(mlx_img, x, y, 0x66CCFF);
			}
			else
				my_mlx_pixel_put(mlx_img, x, y, map[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, mlx_img->img, 0, 0);
}

void	rotate(t_config *config, int keycode)
{
	double oldDirX = config->dirX;
	double oldPlaneX = config->planeX;
	if(keycode == KEY_D)
	{
		config->dirX = config->dirX * cos(- ROTSPEED) - config->dirY * sin(- ROTSPEED);
		config->dirY = oldDirX * sin(- ROTSPEED) + config->dirY * cos(- ROTSPEED);
		config->planeX = config->planeX * cos(- ROTSPEED) - config->planeY * sin(- ROTSPEED);
		config->planeY = oldPlaneX * sin(- ROTSPEED) + config->planeY * cos(- ROTSPEED);
	}
	else if(keycode == KEY_A)
	{
		config->dirX = config->dirX * cos( ROTSPEED) - config->dirY * sin( ROTSPEED);
		config->dirY = oldDirX * sin( ROTSPEED) + config->dirY * cos( ROTSPEED);
		config->planeX = config->planeX * cos( ROTSPEED) - config->planeY * sin( ROTSPEED);
		config->planeY = oldPlaneX * sin( ROTSPEED) + config->planeY * cos( ROTSPEED);
	}
}

void	move(t_config *config, int keycode)
{
	if(keycode == KEY_W)
	{
		config->posX += config->dirX * MOVESPEED;
		config->posY += config->dirY * MOVESPEED;
	}
	else if(keycode == KEY_S)
	{
		config->posX -= config->dirX * MOVESPEED;
		config->posY -= config->dirY * MOVESPEED;
	}
}

int key_press(int keycode, void *param)
{
    t_config *config = (t_config *)param;

    printf("config details: posX=%f, posY=%f, dirX=%f, dirY=%f, planeX=%f, planeY=%f\n",
        config->posX, config->posY, config->dirX, config->dirY, config->planeX, config->planeY);

    printf("Key pressed: %d\n", keycode);
    if(keycode == KEY_W || keycode == KEY_S)
		move(config, keycode);
	else if(keycode == KEY_D || keycode == KEY_A)
		rotate(config, keycode);
    if(keycode == KEY_ESCAPE)
		// Gérer la sortie du programme
	config->map = raycast(config->worldmap, config->posX, config->posY, config->dirX, config->dirY, config->planeX, config->planeY);
	printf("Drawing scene...\n");
	draw_scene(config->map, config->mlx, config->mlx_win, config->mlx_img);
	printf("Scene drawn.\n");
    return (0);
}

void 			render(t_config *config)
{
    void	*mlx;
    void	*mlx_win;
    t_mlximg	mlx_img;
	
    mlx = mlx_init();
    if(!mlx)
        printf("Error mlx_init\n");
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    if(!mlx_win)
        printf("Error mlx_new_window\n");
    mlx_img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if(!mlx_img.img)
        printf("Error mlx_new_image\n");
    mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel, &mlx_img.line_length,
								&mlx_img.endian);
    draw_scene(map, mlx, mlx_win, &mlx_img);	
    config.mlx_img = &mlx_img;
	config.mlx_win = mlx_win;
	config.mlx = mlx;
    mlx_key_hook(mlx_win, key_press, config);
    mlx_loop(mlx);
}
// int key_press(int keycode, void *param)
// {
//     t_config *config = (t_config *)param;

//     printf("config details: posX=%f, posY=%f, dirX=%f, dirY=%f, planeX=%f, planeY=%f\n",
//         config->posX, config->posY, config->dirX, config->dirY, config->planeX, config->planeY);

//     printf("Key pressed: %d\n", keycode);

//     if(keycode == KEY_W)
//     {
//     //   if(config->map[(int)(config->posX + config->dirX * MOVESPEED)][(int)(config->posY)] == false) 
// 	  config->posX += config->dirX * MOVESPEED;
//     //   if(m©ap_data->map[(int)(config->posX)][(int)(config->posY + config->dirY * MOVESPEED)] == false)
// 	  config->posY += config->dirY * MOVESPEED;
//       printf("After move: x=%d, y=%d\n", (int)config->posX, (int)config->posY);
//     }
// 	else if(keycode == KEY_S)
// 	{
// 	// if(config->map[(int)(config->posX - config->dirX * MOVESPEED)][(int)(config->posY)] == false) 
// 	config->posX -= config->dirX * MOVESPEED;
// 	// if(config->map[(int)(config->posX)][(int)(config->posY - config->dirY * MOVESPEED)] == false) 
// 	config->posY -= config->dirY * MOVESPEED;
// 	printf("After move: x=%d, y=%d\n", (int)config->posX, (int)config->posY);
// 	}
// 	if(keycode == KEY_D)
// 	{
// 		double oldDirX = config->dirX;
// 		config->dirX = config->dirX * cos(- ROTSPEED) - config->dirY * sin(- ROTSPEED);
// 		config->dirY = oldDirX * sin(- ROTSPEED) + config->dirY * cos(- ROTSPEED);
// 		double oldPlaneX = config->planeX;
// 		config->planeX = config->planeX * cos(- ROTSPEED) - config->planeY * sin(- ROTSPEED);
// 		config->planeY = oldPlaneX * sin(- ROTSPEED) + config->planeY * cos(- ROTSPEED);
// 		printf("After rotation: dirX=%f, dirY=%f, planeX=%f, planeY=%f\n", config->dirX, config->dirY, config->planeX, config->planeY);
// 	}
// 	else if(keycode == KEY_A)
// 	{
// 		double oldDirX = config->dirX;
// 		config->dirX = config->dirX * cos( ROTSPEED) - config->dirY * sin( ROTSPEED);
// 		config->dirY = oldDirX * sin( ROTSPEED) + config->dirY * cos( ROTSPEED);
// 		double oldPlaneX = config->planeX;
// 		config->planeX = config->planeX * cos( ROTSPEED) - config->planeY * sin( ROTSPEED);
// 		config->planeY = oldPlaneX * sin( ROTSPEED) + config->planeY * cos( ROTSPEED);
// 		printf("After rotation: dirX=%f, dirY=%f, planeX=%f, planeY=%f\n", config->dirX, config->dirY, config->planeX, config->planeY);
// 	}
//     if(keycode == KEY_ESCAPE)
//     {
//       // Gérer la sortie du programme
//       // Vous devez définir comment vous voulez gérer cette situation
//     }
// 	config->map = raycast(config->worldmap, config->posX, config->posY, config->dirX, config->dirY, config->planeX, config->planeY);
// 	printf("Drawing scene...\n");
// 	draw_scene(config->map, config->mlx, config->mlx_win, config->mlx_img);
// 	printf("Scene drawn.\n");
//     return (0);
// }




// void 			render(int **map, double posX, double posY, double dirX, double dirY, double planeX, double planeY, int **worldmap)
// {
//     void	*mlx;
//     void	*mlx_win;
//     t_mlximg	mlx_img;
//     t_map_data	map_data;
	

	
//     mlx = mlx_init();
//     if(!mlx)
//         printf("Error mlx_init\n");
//     mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
//     if(!mlx_win)
//         printf("Error mlx_new_window\n");
//     mlx_img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
//     if(!mlx_img.img)
//         printf("Error mlx_new_image\n");
//     mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel, &mlx_img.line_length,
// 								&mlx_img.endian);
	
//     draw_scene(map, mlx, mlx_win, &mlx_img);
//     // mlx_put_image_to_window(mlx, mlx_win, mlx_img.img, 0, 0);
	
//     map_data.map = map;
//     map_data.mlx = mlx;
// 	map_data.posX = posX;
// 	map_data.posY = posY;
// 	map_data.dirX = dirX;
// 	map_data.dirY = dirY;
// 	map_data.planeX = planeX;
// 	map_data.planeY = planeY;
//     map_data.mlx_img = &mlx_img;
// 	map_data.mlx_win = mlx_win;
// 	map_data.worldmap = worldmap;
	
//     mlx_key_hook(mlx_win, key_press, &map_data);
// 	// mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
//     mlx_loop(mlx);
// }
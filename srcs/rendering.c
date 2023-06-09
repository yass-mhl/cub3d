#include "cube3d.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESCAPE 65307
#define ROTSPEED 0.1
#define MOVESPEED 0.1

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
			my_mlx_pixel_put(mlx_img, x, y, map[y][x]);
			x++;
		}
		y++;
	}
	printf("------Map------\n");
	printf("Map : %p\n", map);
	printf("mlx : %p\n", mlx);
	printf("mlx_win : %p\n", mlx_win);
	printf("mlx_img : %p\n", mlx_img);
	mlx_put_image_to_window(mlx, mlx_win, mlx_img->img, 0, 0);
}

int key_press(int keycode, void *param)
{
    t_map_data *map_data = (t_map_data *)param;

    printf("map_data details: posX=%f, posY=%f, dirX=%f, dirY=%f, planeX=%f, planeY=%f\n",
        map_data->posX, map_data->posY, map_data->dirX, map_data->dirY, map_data->planeX, map_data->planeY);

    printf("Key pressed: %d\n", keycode);

    if(keycode == KEY_W)
    {
      printf("W\n");
      printf("Moving forward...\n");
      if(map_data->map[(int)(map_data->posX + map_data->dirX * MOVESPEED)][(int)(map_data->posY)] == false) map_data->posX += map_data->dirX * MOVESPEED;
      if(map_data->map[(int)(map_data->posX)][(int)(map_data->posY + map_data->dirY * MOVESPEED)] == false) map_data->posY += map_data->dirY * MOVESPEED;
      printf("After move: x=%d, y=%d\n", (int)map_data->posX, (int)map_data->posY);
    }
	else if(keycode == KEY_S)
	{
	printf("S\n");
	printf("Moving back...\n");
	if(map_data->map[(int)(map_data->posX - map_data->dirX * MOVESPEED)][(int)(map_data->posY)] == false) map_data->posX -= map_data->dirX * MOVESPEED;
	if(map_data->map[(int)(map_data->posX)][(int)(map_data->posY - map_data->dirY * MOVESPEED)] == false) map_data->posY -= map_data->dirY * MOVESPEED;
	printf("After move: x=%d, y=%d\n", (int)map_data->posX, (int)map_data->posY);
	}
	if(keycode == KEY_D)
	{
		printf("D\n");
		printf("Rotating right...\n");
		double oldDirX = map_data->dirX;
		map_data->dirX = map_data->dirX * cos(- ROTSPEED) - map_data->dirY * sin(- ROTSPEED);
		map_data->dirY = oldDirX * sin(- ROTSPEED) + map_data->dirY * cos(- ROTSPEED);
		double oldPlaneX = map_data->planeX;
		map_data->planeX = map_data->planeX * cos(- ROTSPEED) - map_data->planeY * sin(- ROTSPEED);
		map_data->planeY = oldPlaneX * sin(- ROTSPEED) + map_data->planeY * cos(- ROTSPEED);
		printf("After rotation: dirX=%f, dirY=%f, planeX=%f, planeY=%f\n", map_data->dirX, map_data->dirY, map_data->planeX, map_data->planeY);
	}
	else if(keycode == KEY_A)
	{
		printf("A\n");
		printf("Rotating left...\n");
		double oldDirX = map_data->dirX;
		map_data->dirX = map_data->dirX * cos( ROTSPEED) - map_data->dirY * sin( ROTSPEED);
		map_data->dirY = oldDirX * sin( ROTSPEED) + map_data->dirY * cos( ROTSPEED);
		double oldPlaneX = map_data->planeX;
		map_data->planeX = map_data->planeX * cos( ROTSPEED) - map_data->planeY * sin( ROTSPEED);
		map_data->planeY = oldPlaneX * sin( ROTSPEED) + map_data->planeY * cos( ROTSPEED);
		printf("After rotation: dirX=%f, dirY=%f, planeX=%f, planeY=%f\n", map_data->dirX, map_data->dirY, map_data->planeX, map_data->planeY);
	}
    if(keycode == KEY_ESCAPE)
    {
      // Gérer la sortie du programme
      // Vous devez définir comment vous voulez gérer cette situation
    }
	map_data->map = raycast(map_data->worldmap, map_data->posX, map_data->posY, map_data->dirX, map_data->dirY, map_data->planeX, map_data->planeY);
	printf("Drawing scene...\n");
	draw_scene(map_data->map, map_data->mlx, map_data->mlx_win, map_data->mlx_img);
	printf("Scene drawn.\n");
    return (0);
}

void 			render(int **map, double posX, double posY, double dirX, double dirY, double planeX, double planeY, int **worldmap)
{
    void	*mlx;
    void	*mlx_win;
    t_mlximg	mlx_img;
    t_map_data	map_data;
	

	
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
    // mlx_put_image_to_window(mlx, mlx_win, mlx_img.img, 0, 0);
	
    map_data.map = map;
    map_data.mlx = mlx;
	map_data.posX = posX;
	map_data.posY = posY;
	map_data.dirX = dirX;
	map_data.dirY = dirY;
	map_data.planeX = planeX;
	map_data.planeY = planeY;
    map_data.mlx_img = &mlx_img;
	map_data.mlx_win = mlx_win;
	map_data.worldmap = worldmap;
	
    mlx_key_hook(mlx_win, key_press, &map_data);
	// mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
    mlx_loop(mlx);
}

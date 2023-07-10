/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:35:16 by gansard           #+#    #+#             */
/*   Updated: 2023/07/10 18:10:41 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlximg *mlximg, int x, int y, int color)
{
	char	*dst;

	dst = mlximg->addr + (y * mlximg->line_length + x * (mlximg->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	init_mlx_img(void *mlx, t_mlximg *mlx_img)
{
	if (mlx_img->img)
		mlx_destroy_image(mlx, mlx_img->img);
	ft_memset(mlx_img, 0, sizeof(t_mlximg));
	mlx_img->img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx_img->img)
		printf("Error mlx_new_image\n");
	mlx_img->addr = mlx_get_data_addr(mlx_img->img, &mlx_img->bits_per_pixel,
			&mlx_img->line_length, &mlx_img->endian);
}

void	draw_map_to_image(int **map, t_mlximg *mlx_img)
{
	int			y;
	int			x;
	t_config	*config;

	config = get_config();
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (map[y][x] == -1)
			{
				if (y > WINDOW_HEIGHT / 2)
					my_mlx_pixel_put(mlx_img, x, y, config->hexa_f);
				else
					my_mlx_pixel_put(mlx_img, x, y, config->hexa_c);
			}
			else
				my_mlx_pixel_put(mlx_img, x, y, map[y][x]);
			x++;
		}
		y++;
	}
}

void	draw_scene(int **map, void *mlx, void *mlx_win, t_mlximg *mlx_img)
{
	init_mlx_img(mlx, mlx_img);
	draw_map_to_image(map, mlx_img);
	mlx_put_image_to_window(mlx, mlx_win, mlx_img->img, 0, 0);
}

void	render(t_config *config)
{
	t_mlximg	mlx_img;

	config->mlx_win = mlx_new_window(config->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	if (!config->mlx_win)
		printf("Error mlx_new_window\n");
	ft_memset(&mlx_img, 0, sizeof(t_mlximg));
	draw_scene(config->pixelMap, config->mlx, config->mlx_win, &mlx_img);
	config->mlx_img = &mlx_img;
	mlx_hook(config->mlx_win, KeyPress, KeyPressMask, key_press, config);
	mlx_hook(config->mlx_win, 17, 0, &ft_exit, config);
	mlx_loop(config->mlx);
}

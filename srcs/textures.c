/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:15:02 by ymehlil           #+#    #+#             */
/*   Updated: 2023/07/20 12:59:42 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_img(t_config *config, t_mlximg *image, char *path)
{
	image->img = NULL;
	image->addr = NULL;
	image->bits_per_pixel = 0;
	image->line_length = 0;
	image->endian = 0;
	image->img = mlx_xpm_file_to_image(config->mlx, path, &config->h,
			&config->w);
	if (image->img == NULL)
		return ;
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}

static int	*xpm_to_img(t_config *config, char *path)
{
	t_mlximg	tmp;
	int			*buffer;
	int			*tmp_addr;
	int			x;
	int			y;

	init_texture_img(config, &tmp, path);
	buffer = ft_calloc(1, sizeof * buffer * config->h * config->w);
	if (!buffer)
		return (NULL);
	tmp_addr = (int *)tmp.addr;
	y = 0;
	while (y < config->h)
	{
		x = config->w - 1;
		while (x >= 0)
		{
			buffer[y * config->w + (config->w - 1 - x)] = tmp_addr[y * config->w
				+ x];
			--x;
		}
		++y;
	}
	mlx_destroy_image(config->mlx, tmp.img);
	return (buffer);
}

int	**create_textures(void)
{
	int	**texture;

	texture = ft_calloc(4, sizeof * texture);
	return (texture);
}

void	populate_textures(t_config *config, int **texture)
{
	config->mlx = mlx_init();
	if (config->mlx == NULL)
	{
		printf("Error\ncub3d: mlx_init\n");
		ft_exit(config);
	}
	texture[0] = xpm_to_img(config, config->no);
	texture[1] = xpm_to_img(config, config->so);
	texture[2] = xpm_to_img(config, config->ea);
	texture[3] = xpm_to_img(config, config->we);
}

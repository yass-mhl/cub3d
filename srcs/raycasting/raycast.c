/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:27:02 by gansard           #+#    #+#             */
/*   Updated: 2023/07/19 16:12:29 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	**allocate_buffer(void)
{
	int	**buffer;
	int	iter_y;

	buffer = ft_calloc(WINDOW_HEIGHT + 1, sizeof(int *));
	if (!buffer)
		return (NULL);
	iter_y = 0;
	while (iter_y < WINDOW_HEIGHT)
	{
		buffer[iter_y] = ft_calloc(WINDOW_WIDTH + 1, sizeof(int));
		ft_memset(buffer[iter_y], -1, WINDOW_WIDTH * sizeof(int));
		if (!buffer[iter_y])
			printf("Failed to allocate memory for buffer[%d]\n",
				iter_y);
		iter_y++;
	}
	return (buffer);
}

int	**draw_pixels(t_rc rc)
{
	double	step;
	double	tex_pos;
	int		iter_y;
	int		tex_y;
	int		color;

	step = 1.0 * TEXHEIGHT / rc.line_height;
	tex_pos = (rc.draw_start - WINDOW_HEIGHT / 2 + rc.line_height / 2) * step;
	iter_y = rc.draw_start;
	while (iter_y < rc.draw_end)
	{
		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += step;
		color = rc.texture[rc.tex_num][TEXHEIGHT * tex_y + rc.tex_x];
		rc.buffer[iter_y][rc.x] = color;
		iter_y++;
	}
	return (rc.buffer);
}

void	raycasting(t_config *config)
{
	t_rc	rc;
	int		iter_x;

	iter_x = 0;
	while (iter_x < WINDOW_WIDTH)
	{
		rc = init_rc(config, iter_x);
		rc = update_rc(rc, config);
		process_rc(&rc, config);
		iter_x++;
	}
}

int	**raycast(t_config *config)
{
	int	**buffer;

	if (config->pixelmap)
		ft_free_all_tab_int(config->pixelmap);
	buffer = allocate_buffer();
	if (!buffer)
	{
		printf("Failed to allocate memory for screen buffer\n");
		return (NULL);
	}
	config->pixelmap = buffer;
	raycasting(config);
	return (buffer);
}

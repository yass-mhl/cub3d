/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:34:36 by gansard           #+#    #+#             */
/*   Updated: 2023/07/03 11:32:54 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3d.h"

//int	**allocate_buffer(void)
//{
//	int	**buffer;
//	int	iter_y;

//	buffer = calloc(WINDOW_HEIGHT + 1, sizeof(int *));
//	if (!buffer)
//		return (NULL);
//	iter_y = 0;
//	while (iter_y < WINDOW_HEIGHT)
//	{
//		buffer[iter_y] = calloc(WINDOW_WIDTH + 1, sizeof(int));
//		memset(buffer[iter_y], -1, WINDOW_WIDTH * sizeof(int));
//		if (!buffer[iter_y])
//			fprintf(stderr, "Failed to allocate memory for buffer[%d]\n",
//				iter_y);
//		iter_y++;
//	}
//	return (buffer);
//}

//int	**draw_pixels(t_rc rc)
//{
//	double	step;
//	double	tex_pos;
//	int		iter_y;
//	int		tex_y;
//	int		color;

//	step = 1.0 * TEXHEIGHT / rc.line_height;
//	tex_pos = (rc.draw_start - WINDOW_HEIGHT / 2 + rc.line_height / 2) * step;
//	iter_y = rc.draw_start;
//	while (iter_y < rc.draw_end)
//	{
//		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
//		tex_pos += step;
//		color = rc.texture[rc.tex_num][TEXHEIGHT * tex_y + rc.tex_x];
//		rc.buffer[iter_y][rc.x] = color;
//		iter_y++;
//	}
//	return (rc.buffer);
//}

//t_rc	init_ray_dir_and_delta_dist(t_rc rc)
//{
//	if (rc.ray_dir_x == 0)
//		rc.delta_dist_x = 1e30;
//	else
//		rc.delta_dist_x = fabs(1 / rc.ray_dir_x);
//	if (rc.ray_dir_y == 0)
//		rc.delta_dist_y = 1e30;
//	else
//		rc.delta_dist_y = fabs(1 / rc.ray_dir_y);
//	return (rc);
//}

//t_rc	init_side_dist(t_rc rc, t_config *config)
//{
//	if (rc.ray_dir_x < 0)
//	{
//		rc.step_x = -1;
//		rc.side_dist_x = (config->p_pos_x - rc.map_x) * rc.delta_dist_x;
//	}
//	else
//	{
//		rc.step_x = 1;
//		rc.side_dist_x = (rc.map_x + 1.0 - config->p_pos_x) * rc.delta_dist_x;
//	}
//	if (rc.ray_dir_y < 0)
//	{
//		rc.step_y = -1;
//		rc.side_dist_y = (config->p_pos_y - rc.map_y) * rc.delta_dist_y;
//	}
//	else
//	{
//		rc.step_y = 1;
//		rc.side_dist_y = (rc.map_y + 1.0 - config->p_pos_y) * rc.delta_dist_y;
//	}
//	return (rc);
//}

//t_rc	init_rc(t_config *config, int iter_x)
//{
//	t_rc	rc;

//	rc.iter_x = iter_x;
//	rc.camera_x = 2 * rc.iter_x / (double)WINDOW_WIDTH - 1;
//	rc.ray_dir_x = config->dirx + config->plane_x * rc.camera_x;
//	rc.ray_dir_y = config->diry + config->plane_y * rc.camera_x;
//	rc.map_x = (int)config->p_pos_x;
//	rc.map_y = (int)config->p_pos_y;
//	rc.hit = 0;
//	rc = init_ray_dir_and_delta_dist(rc);
//	rc = init_side_dist(rc, config);
//	return (rc);
//}

//t_rc	update_hit_and_side(t_rc rc, t_config *config)
//{
//	while (rc.hit == 0)
//	{
//		if (rc.side_dist_x < rc.side_dist_y)
//		{
//			rc.side_dist_x += rc.delta_dist_x;
//			rc.map_x += rc.step_x;
//			rc.side = 0;
//		}
//		else
//		{
//			rc.side_dist_y += rc.delta_dist_y;
//			rc.map_y += rc.step_y;
//			rc.side = 1;
//		}
//		if (config->map->map[rc.map_y][rc.map_x] == '1')
//			rc.hit = 1;
//	}
//	return (rc);
//}

//t_rc	update_rc(t_rc rc, t_config *config)
//{
//	rc = update_hit_and_side(rc, config);
//	if (rc.side == 0)
//		rc.perp_wall_dist = rc.side_dist_x - rc.delta_dist_x;
//	else
//		rc.perp_wall_dist = rc.side_dist_y - rc.delta_dist_y;
//	rc.line_height = (int)(WINDOW_HEIGHT / rc.perp_wall_dist);
//	rc.draw_start = -rc.line_height / 2 + WINDOW_HEIGHT / 2;
//	if (rc.draw_start < 0)
//		rc.draw_start = 0;
//	rc.draw_end = rc.line_height / 2 + WINDOW_HEIGHT / 2;
//	if (rc.draw_end >= WINDOW_HEIGHT)
//		rc.draw_end = WINDOW_HEIGHT;
//	return (rc);
//}

//void	set_tex_num(t_rc *rc)
//{
//	if (rc->side == 0)
//	{
//		if (rc->step_x > 0)
//			rc->tex_num = 2;
//		else
//			rc->tex_num = 3;
//	}
//	else
//	{
//		if (rc->step_y > 0)
//			rc->tex_num = 1;
//		else
//			rc->tex_num = 0;
//	}
//}

//void	set_wall_x(t_rc *rc, t_config *config)
//{
//	if (rc->side == 0)
//		rc->wall_x = config->p_pos_y + rc->perp_wall_dist * rc->ray_dir_y;
//	else
//		rc->wall_x = config->p_pos_x + rc->perp_wall_dist * rc->ray_dir_x;
//	rc->wall_x -= floor((rc->wall_x));
//	rc->tex_x = (int)(rc->wall_x * (double)TEXWIDTH);
//	if (rc->side == 0 && rc->ray_dir_x > 0)
//		rc->tex_x = TEXWIDTH - rc->tex_x - 1;
//	if (rc->side == 1 && rc->ray_dir_y < 0)
//		rc->tex_x = TEXWIDTH - rc->tex_x - 1;
//}

//void	process_rc(t_rc *rc, t_config *config)
//{
//	set_tex_num(rc);
//	set_wall_x(rc, config);
//	rc->buffer = config->pixelMap;
//	rc->x = rc->iter_x;
//	rc->texture = config->textures;
//	draw_pixels(*rc);
//}

//void	raycasting(t_config *config)
//{
//	t_rc	rc;
//	int		iter_x;

//	iter_x = 0;
//	while (iter_x < WINDOW_WIDTH)
//	{
//		rc = init_rc(config, iter_x);
//		rc = update_rc(rc, config);
//		process_rc(&rc, config);
//		iter_x++;
//	}
//}

//int	**raycast(t_config *config)
//{
//	int	**buffer;

//	if (config->pixelMap)
//		ft_free_all_tab_int(config->pixelMap);
//	buffer = allocate_buffer();
//	if (!buffer)
//	{
//		fprintf(stderr, "Failed to allocate memory for screen buffer\n");
//		return (NULL);
//	}
//	config->pixelMap = buffer;
//	raycasting(config);
//	return (buffer);
//}

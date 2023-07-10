/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:26:22 by gansard           #+#    #+#             */
/*   Updated: 2023/07/03 11:42:00 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rc	init_ray_dir_and_delta_dist(t_rc rc)
{
	if (rc.ray_dir_x == 0)
		rc.delta_dist_x = 1e30;
	else
		rc.delta_dist_x = fabs(1 / rc.ray_dir_x);
	if (rc.ray_dir_y == 0)
		rc.delta_dist_y = 1e30;
	else
		rc.delta_dist_y = fabs(1 / rc.ray_dir_y);
	return (rc);
}

static t_rc	init_side_dist(t_rc rc, t_config *config)
{
	if (rc.ray_dir_x < 0)
	{
		rc.step_x = -1;
		rc.side_dist_x = (config->p_pos_x - rc.map_x) * rc.delta_dist_x;
	}
	else
	{
		rc.step_x = 1;
		rc.side_dist_x = (rc.map_x + 1.0 - config->p_pos_x) * rc.delta_dist_x;
	}
	if (rc.ray_dir_y < 0)
	{
		rc.step_y = -1;
		rc.side_dist_y = (config->p_pos_y - rc.map_y) * rc.delta_dist_y;
	}
	else
	{
		rc.step_y = 1;
		rc.side_dist_y = (rc.map_y + 1.0 - config->p_pos_y) * rc.delta_dist_y;
	}
	return (rc);
}

t_rc	init_rc(t_config *config, int iter_x)
{
	t_rc	rc;

	rc.iter_x = iter_x;
	rc.camera_x = 2 * rc.iter_x / (double)WINDOW_WIDTH - 1;
	rc.ray_dir_x = config->dirx + config->plane_x * rc.camera_x;
	rc.ray_dir_y = config->diry + config->plane_y * rc.camera_x;
	rc.map_x = (int)config->p_pos_x;
	rc.map_y = (int)config->p_pos_y;
	rc.hit = 0;
	rc = init_ray_dir_and_delta_dist(rc);
	rc = init_side_dist(rc, config);
	return (rc);
}

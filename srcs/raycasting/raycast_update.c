/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:26:38 by gansard           #+#    #+#             */
/*   Updated: 2023/07/12 17:10:54 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rc	update_hit_and_side(t_rc rc, t_config *config)
{
	while (rc.hit == 0)
	{
		if (rc.side_dist_x < rc.side_dist_y)
		{
			rc.side_dist_x += rc.delta_dist_x;
			rc.map_x += rc.step_x;
			rc.side = 0;
		}
		else
		{
			rc.side_dist_y += rc.delta_dist_y;
			rc.map_y += rc.step_y;
			rc.side = 1;
		}
		if (config->map->map[rc.map_y][rc.map_x] == '1')
			rc.hit = 1;
	}
	return (rc);
}

t_rc	update_rc(t_rc rc, t_config *config)
{
	rc = update_hit_and_side(rc, config);
	if (rc.side == 0)
		rc.perp_wall_dist = rc.side_dist_x - rc.delta_dist_x;
	else
		rc.perp_wall_dist = rc.side_dist_y - rc.delta_dist_y;
	if (rc.perp_wall_dist < 0.0001)
		rc.perp_wall_dist = 0.0001;
	rc.line_height = (int)(WINDOW_HEIGHT / rc.perp_wall_dist);
	rc.draw_start = -rc.line_height / 2 + WINDOW_HEIGHT / 2;
	if (rc.draw_start < 0)
		rc.draw_start = 0;
	rc.draw_end = rc.line_height / 2 + WINDOW_HEIGHT / 2;
	if (rc.draw_end >= WINDOW_HEIGHT)
		rc.draw_end = WINDOW_HEIGHT;
	return (rc);
}

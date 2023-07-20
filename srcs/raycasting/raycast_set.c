/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:26:49 by gansard           #+#    #+#             */
/*   Updated: 2023/07/19 16:12:29 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_tex_num(t_rc *rc)
{
	if (rc->side == 0)
	{
		if (rc->step_x > 0)
			rc->tex_num = 2;
		else
			rc->tex_num = 3;
	}
	else
	{
		if (rc->step_y > 0)
			rc->tex_num = 1;
		else
			rc->tex_num = 0;
	}
}

static void	set_wall_x(t_rc *rc, t_config *config)
{
	if (rc->side == 0)
		rc->wall_x = config->p_pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = config->p_pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor((rc->wall_x));
	rc->tex_x = (int)(rc->wall_x * (double)TEXWIDTH);
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->tex_x = TEXWIDTH - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->tex_x = TEXWIDTH - rc->tex_x - 1;
}

void	process_rc(t_rc *rc, t_config *config)
{
	set_tex_num(rc);
	set_wall_x(rc, config);
	rc->buffer = config->pixelmap;
	rc->x = rc->iter_x;
	rc->texture = config->textures;
	draw_pixels(*rc);
}

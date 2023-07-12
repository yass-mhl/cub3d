/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:55:57 by gansard           #+#    #+#             */
/*   Updated: 2023/07/11 15:58:22 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_direction_left(t_config *config, double olddirx,
		double oldplane_x)
{
	config->dirx = config->dirx * cos(-ROTSPEED) - config->diry
		* sin(-ROTSPEED);
	config->diry = olddirx * sin(-ROTSPEED) + config->diry * cos(-ROTSPEED);
	config->plane_x = config->plane_x * cos(-ROTSPEED) - config->plane_y
		* sin(-ROTSPEED);
	config->plane_y = oldplane_x * sin(-ROTSPEED) + config->plane_y
		* cos(-ROTSPEED);
}

static void	update_direction_right(t_config *config, double olddirx,
		double oldplane_x)
{
	config->dirx = config->dirx * cos(ROTSPEED) - config->diry * sin(ROTSPEED);
	config->diry = olddirx * sin(ROTSPEED) + config->diry * cos(ROTSPEED);
	config->plane_x = config->plane_x * cos(ROTSPEED) - config->plane_y
		* sin(ROTSPEED);
	config->plane_y = oldplane_x * sin(ROTSPEED) + config->plane_y
		* cos(ROTSPEED);
}

void	rotate(t_config *config, int keycode)
{
	double	olddirx;
	double	oldplane_x;

	olddirx = config->dirx;
	oldplane_x = config->plane_x;
	if (keycode == KEYLEFT)
		update_direction_left(config, olddirx, oldplane_x);
	else if (keycode == KEYRIGHT)
		update_direction_right(config, olddirx, oldplane_x);
}

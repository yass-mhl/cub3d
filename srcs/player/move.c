/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:54:48 by gansard           #+#    #+#             */
/*   Updated: 2023/07/10 16:01:35 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_direction_a(t_config *config, double strafe_dir_x,
		double strafe_dir_y, double strafe_speed)
{
	if (config->map->map[(int)(config->p_pos_y)][(int)(config->p_pos_x
			- strafe_dir_x * strafe_speed)] != '1')
		config->p_pos_x -= strafe_dir_x * strafe_speed;
	if (config->map->map[(int)(config->p_pos_y - strafe_dir_y
			* strafe_speed)][(int)(config->p_pos_x)] != '1')
		config->p_pos_y -= strafe_dir_y * strafe_speed;
}

static void	move_direction_d(t_config *config, double strafe_dir_x,
		double strafe_dir_y, double strafe_speed)
{
	if (config->map->map[(int)(config->p_pos_y)][(int)(config->p_pos_x
			+ strafe_dir_x * strafe_speed)] != '1')
		config->p_pos_x += strafe_dir_x * strafe_speed;
	if (config->map->map[(int)(config->p_pos_y + strafe_dir_y
			* strafe_speed)][(int)(config->p_pos_x)] != '1')
		config->p_pos_y += strafe_dir_y * strafe_speed;
}

static void	move_forward(t_config *config)
{
	int		new_x;
	int		new_y;
	char	cell;

	new_x = (int)(config->p_pos_x + config->dirx * MOVESPEED);
	new_y = (int)(config->p_pos_y + config->diry * MOVESPEED);
	if (config->map->map[(int)(config->p_pos_y)][new_x] != '1')
	{
		cell = config->map->map[(int)(config->p_pos_y)][new_x];
		config->p_pos_x += config->dirx * MOVESPEED;
	}
	if (config->map->map[new_y][(int)(config->p_pos_x)] != '1')
	{
		cell = config->map->map[new_y][(int)config->p_pos_x];
		config->p_pos_y += config->diry * MOVESPEED;
	}
}

static void	move_backward(t_config *config)
{
	int		new_x;
	int		new_y;
	char	cell;

	new_x = (int)(config->p_pos_x - config->dirx * MOVESPEED);
	new_y = (int)(config->p_pos_y - config->diry * MOVESPEED);
	if (config->map->map[(int)(config->p_pos_y)][new_x] != '1')
	{
		cell = config->map->map[(int)(config->p_pos_y)][new_x];
		config->p_pos_x -= config->dirx * MOVESPEED;
	}
	if (config->map->map[new_y][(int)(config->p_pos_x)] != '1')
	{
		cell = config->map->map[new_y][(int)config->p_pos_x];
		config->p_pos_y -= config->diry * MOVESPEED;
	}
}

void	move(t_config *config, int keycode)
{
	double	strafe_dir_x;
	double	strafe_dir_y;
	double	strafe_speed;

	strafe_speed = MOVESPEED;
	strafe_dir_y = config->dirx;
	strafe_dir_x = -config->diry;
	if (keycode == KEYD)
		move_direction_d(config, strafe_dir_x, strafe_dir_y, strafe_speed);
	else if (keycode == KEYA)
		move_direction_a(config, strafe_dir_x, strafe_dir_y, strafe_speed);
	else if (keycode == KEYW)
		move_forward(config);
	else if (keycode == KEYS)
		move_backward(config);
}

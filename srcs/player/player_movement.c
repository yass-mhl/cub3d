/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:12:22 by gansard           #+#    #+#             */
/*   Updated: 2023/07/03 11:59:34 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3d.h"

//void	update_direction_left(t_config *config, double olddirx,
//		double oldplane_x)
//{
//	printf("x = %f\n", config->p_pos_x);
//	printf("y = %f\n", config->p_pos_y);
//	config->dirx = config->dirx * cos(-ROTSPEED) - config->diry
//		* sin(-ROTSPEED);
//	config->diry = olddirx * sin(-ROTSPEED) + config->diry * cos(-ROTSPEED);
//	config->plane_x = config->plane_x * cos(-ROTSPEED) - config->plane_y
//		* sin(-ROTSPEED);
//	config->plane_y = oldplane_x * sin(-ROTSPEED) + config->plane_y
//		* cos(-ROTSPEED);
//}

//void	update_direction_right(t_config *config, double olddirx,
//		double oldplane_x)
//{
//	printf("x = %f\n", config->p_pos_x);
//	printf("y = %f\n", config->p_pos_y);
//	config->dirx = config->dirx * cos(ROTSPEED) - config->diry * sin(ROTSPEED);
//	config->diry = olddirx * sin(ROTSPEED) + config->diry * cos(ROTSPEED);
//	config->plane_x = config->plane_x * cos(ROTSPEED) - config->plane_y
//		* sin(ROTSPEED);
//	config->plane_y = oldplane_x * sin(ROTSPEED) + config->plane_y
//		* cos(ROTSPEED);
//}

//void	rotate(t_config *config, int keycode)
//{
//	double	olddirx;
//	double	oldplane_x;

//	olddirx = config->dirx;
//	oldplane_x = config->plane_x;
//	if (keycode == KEYLEFT)
//		update_direction_left(config, olddirx, oldplane_x);
//	else if (keycode == KEYRIGHT)
//		update_direction_right(config, olddirx, oldplane_x);
//}

//void	move_direction_a(t_config *config, double strafe_dir_x,
//		double strafe_dir_y, double strafe_speed)
//{
//	if (config->map->map[(int)(config->p_pos_y)][(int)(config->p_pos_x
//			- strafe_dir_x * strafe_speed)] != '1')
//		config->p_pos_x -= strafe_dir_x * strafe_speed;
//	if (config->map->map[(int)(config->p_pos_y - strafe_dir_y
//			* strafe_speed)][(int)(config->p_pos_x)] != '1')
//		config->p_pos_y -= strafe_dir_y * strafe_speed;
//}

//void	move_direction_d(t_config *config, double strafe_dir_x,
//		double strafe_dir_y, double strafe_speed)
//{
//	if (config->map->map[(int)(config->p_pos_y)][(int)(config->p_pos_x
//			+ strafe_dir_x * strafe_speed)] != '1')
//		config->p_pos_x += strafe_dir_x * strafe_speed;
//	if (config->map->map[(int)(config->p_pos_y + strafe_dir_y
//			* strafe_speed)][(int)(config->p_pos_x)] != '1')
//		config->p_pos_y += strafe_dir_y * strafe_speed;
//}

//void	move_forward(t_config *config)
//{
//	int		new_x;
//	int		new_y;
//	char	cell;

//	new_x = (int)(config->p_pos_x + config->dirx * MOVESPEED);
//	new_y = (int)(config->p_pos_y + config->diry * MOVESPEED);
//	if (config->map->map[(int)(config->p_pos_y)][new_x] != '1')
//	{
//		cell = config->map->map[(int)(config->p_pos_y)][new_x];
//		config->p_pos_x += config->dirx * MOVESPEED;
//	}
//	if (config->map->map[new_y][(int)(config->p_pos_x)] != '1')
//	{
//		cell = config->map->map[new_y][(int)config->p_pos_x];
//		config->p_pos_y += config->diry * MOVESPEED;
//	}
//}

//void	move_backward(t_config *config)
//{
//	int		new_x;
//	int		new_y;
//	char	cell;

//	new_x = (int)(config->p_pos_x + config->dirx * MOVESPEED);
//	new_y = (int)(config->p_pos_y + config->diry * MOVESPEED);
//	if (config->map->map[(int)(config->p_pos_y)][new_x] != '1')
//	{
//		cell = config->map->map[(int)(config->p_pos_y)][new_x];
//		config->p_pos_x -= config->dirx * MOVESPEED;
//	}
//	if (config->map->map[new_y][(int)(config->p_pos_x)] != '1')
//	{
//		cell = config->map->map[new_y][(int)config->p_pos_x];
//		config->p_pos_y -= config->diry * MOVESPEED;
//	}
//}

//void	move(t_config *config, int keycode)
//{
//	double	strafe_dir_x;
//	double	strafe_dir_y;
//	double	strafe_speed;

//	strafe_speed = MOVESPEED;
//	strafe_dir_y = config->dirx;
//	strafe_dir_x = -config->diry;
//	if (keycode == KEYD)
//		move_direction_d(config, strafe_dir_x, strafe_dir_y, strafe_speed);
//	else if (keycode == KEYA)
//		move_direction_a(config, strafe_dir_x, strafe_dir_y, strafe_speed);
//	else if (keycode == KEYW)
//		move_forward(config);
//	else if (keycode == KEYS)
//		move_backward(config);
//}

//void	process_key(int keycode, t_config *config)
//{
//	if (keycode == KEYW || keycode == KEYS || keycode == KEYD
//		|| keycode == KEYA)
//		move(config, keycode);
//	else if (keycode == KEYRIGHT || keycode == KEYLEFT)
//		rotate(config, keycode);
//	if (keycode == KEY_ESCAPE)
//		ft_exit(config);
//}

//int	key_press(int keycode, void *param)
//{
//	t_config	*config;

//	printf("keycode : %d\n", keycode);
//	config = (t_config *)param;
//	process_key(keycode, config);
//	config->pixelMap = raycast(config);
//	draw_scene(config->pixelMap, config->mlx, config->mlx_win, config->mlx_img);
//	return (0);
//}

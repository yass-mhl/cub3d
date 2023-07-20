/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:54:10 by gansard           #+#    #+#             */
/*   Updated: 2023/07/19 16:12:29 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_key(int keycode, t_config *config)
{
	if (keycode == KEYW || keycode == KEYS || keycode == KEYD
		|| keycode == KEYA)
		move(config, keycode);
	else if (keycode == KEYRIGHT || keycode == KEYLEFT)
		rotate(config, keycode);
	if (keycode == KEY_ESCAPE)
		ft_exit(config);
}

int	key_press(int keycode, void *param)
{
	t_config	*config;

	config = (t_config *)param;
	process_key(keycode, config);
	config->pixelmap = raycast(config);
	draw_scene(config->pixelmap, config->mlx, config->mlx_win, config->mlx_img);
	return (0);
}

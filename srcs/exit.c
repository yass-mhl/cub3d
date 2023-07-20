/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:52:24 by gansard           #+#    #+#             */
/*   Updated: 2023/07/20 12:49:06 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_config *config)
{
	if (config->mlx)
	{
		if (config->mlx_img->img)
			mlx_destroy_image(config->mlx, config->mlx_img->img);
		if (config->mlx_win)
		{
			mlx_clear_window(config->mlx, config->mlx_win);
			mlx_destroy_window(config->mlx, config->mlx_win);
		}
		mlx_destroy_display(config->mlx);
	}
	free_data(config->map);
	free_config(config);
	exit(0);
}

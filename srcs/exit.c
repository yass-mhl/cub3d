/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:52:24 by gansard           #+#    #+#             */
/*   Updated: 2023/07/03 17:28:51 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(t_config *config)
{
	mlx_destroy_image(config->mlx, config->mlx_img->img);
	mlx_clear_window(config->mlx, config->mlx_win);
	mlx_destroy_window(config->mlx, config->mlx_win);
	mlx_destroy_display(config->mlx);
	free_data(config->map);
	free_config(config);
	exit(0);
}
